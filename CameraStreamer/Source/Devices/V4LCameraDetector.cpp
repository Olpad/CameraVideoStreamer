#include "V4LCameraDetector.h"
#include "boost/filesystem.hpp"
#include <streambuf>
#include <fstream>
#include <sstream>
#include "../Exceptions/ConfigRecordReadFailedException.h"
#include "../Configuration/KnownConfigKeys.h"

V4LCameraDetector::V4LCameraDetector(Context* context)
{
	m_context = context;

	try
	{
		m_pathToV4lDir = m_context->ConfigurationReader->GetKeyStringValue(KnownConfigKeys::V4L_DIR_PATH);
	}
	catch(const ConfigRecordReadFailedException& ex)
	{
		std::string error = "In CameraDetector: " + std::string(ex.what()) + ". Using default path: " + DEFAULT_V4L_PATH;
		m_context->Logger->WriteError(error);
		m_pathToV4lDir = DEFAULT_V4L_PATH;
	}
}

const std::map<CameraPath, CameraName>& V4LCameraDetector::DetectSystemCameras()
{
	using namespace boost::filesystem;

	m_detectedCameras.clear();

	path v4lDir(m_pathToV4lDir);
	if(exists(v4lDir) && is_directory(v4lDir))
	{
		// for each directory add new camera if it has a valid name file inside
		for(directory_iterator it(v4lDir); it != directory_iterator(); ++it)
		{
			if (is_directory(it->status()))
			{
				path cameraNamePath = path(std::string((it->path()).string()).append("/name"));
				if(is_regular_file(cameraNamePath))
				{
					std::ifstream fs(cameraNamePath.string().c_str(), std::ios::in | std::ios::binary);
					if(!fs)
						continue;

					std::ostringstream cameraName;
					cameraName << fs.rdbuf();

					m_detectedCameras["/dev/" + it->path().filename().string()] = cameraName.str();
					m_context->Logger->WriteInfo("Detected camera in path: " + cameraNamePath.string()
																									+ " - " + cameraName.str());

					fs.close();
				}
			}
		}
	}

	return m_detectedCameras;
}

const std::map<CameraPath, CameraName>& V4LCameraDetector::GetDetectedCameras() const
{
	return m_detectedCameras;
}

bool V4LCameraDetector::ValidateCamera(const std::string& systemPath)
{
	// todo or to remove since ioctl causes problems in cpp project
	return true;
}

std::set<CameraCapsRecord> V4LCameraDetector::DetectCapabilities(
		const std::string& systemPath)
{
	std::set<CameraCapsRecord> capsRecords;
   GstStateChangeReturn ret;
   GstElement *camera, *sink, *pipeline;

   // prepare elements
   camera = gst_element_factory_make ("v4l2src", "camera");
   sink = gst_element_factory_make ("fakesink", "sink");
   pipeline = gst_pipeline_new ("detection-pipeline");

   if (!camera || !sink || !pipeline )
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - Creation of detection-pipeline failed.");
      return capsRecords;
   }

   // set properties
   g_object_set (sink, "sync", false, NULL);
   g_object_set (camera, "device", systemPath.c_str(), NULL);

   // create and link pipeline
   gst_bin_add_many (GST_BIN (pipeline), camera, sink, NULL);

   if (gst_element_link (camera, sink) != TRUE)
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - linking in detection-pipeline failed.");
      gst_object_unref (pipeline);
      return capsRecords;
   }

   // set pipeline into ready state
   ret = gst_element_set_state (pipeline, GST_STATE_READY);
   if (ret == GST_STATE_CHANGE_FAILURE)
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - cannot go into Ready state.");
      gst_object_unref (pipeline);
      return capsRecords;
   }

   // get capabilities
	m_context->Logger->WriteInfo("Processing camera under given path for available capabilities: " + systemPath);
   FetchCapabilities(camera, capsRecords);

   gst_element_set_state (pipeline, GST_STATE_NULL);
   gst_object_unref (pipeline);

   return capsRecords;
}

void V4LCameraDetector::FetchCapabilities(GstElement* camera, std::set<CameraCapsRecord>& capsSet)
{
   // retrieve pad and caps
   GstPad* pad = gst_element_get_static_pad(camera, "src");
   GstCaps* caps = gst_pad_query_caps(pad, NULL);

   if(!IsAValidCaps(caps))
   	return;

   // parse all capabilities
   GstStructure *structure = NULL;
   for(uint i=0; i < gst_caps_get_size(caps); ++i)
   {
   	structure = gst_caps_get_structure(caps, i);
   	if(!IsAValidStructure(structure))
   		continue;

   	AddNewCapability(structure, capsSet);
   }

   // write diagnostic information
   CapabilitiesDetectionWorkLog(camera, capsSet);
}

bool V4LCameraDetector::IsAValidCaps(GstCaps* caps) const
{
	// validate caps
   if(caps == NULL)
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - Querying NULL camera capabilities.");
   	return false;
   }

   if(gst_caps_is_any(caps))
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - Found an error or a camera with ANY capabilities. The second is kind of unlikely.");
   	return false;
   }

   if(gst_caps_is_empty(caps))
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - Found a camera with EMPTY capabilities.");
   	return false;
   }

   return true;
}

bool V4LCameraDetector::IsAValidStructure(GstStructure* structure) const
{
	if(structure == NULL)
	{
   	m_context->Logger->WriteWarning("Camera capability structure is NULL!");
		return false;
	}

	if(!IsSupportedStructureFormat(structure))
	{
   	m_context->Logger->WriteInfo("Skipping unsupported camera capability: " + std::string(gst_structure_get_name(structure)));
		return false;
	}

	return true;
}

void V4LCameraDetector::AddNewCapability(GstStructure *structure, std::set<CameraCapsRecord>& capsSet)
{
	CameraCapsRecord capsRecord;

	const GValue* framerates = gst_structure_id_get_value (structure, m_framerate);
	if(!GST_VALUE_HOLDS_LIST(framerates) || gst_value_list_get_size (framerates) == 0)
		return;

	std::pair<VideoFormat, AvailableFramerates> newPair;
	auto format = gst_structure_id_get_value (structure, m_format);
	if(!G_IS_VALUE(format) && gst_structure_get_name_id(structure) == m_videoMPEG)
		newPair.first = "MPEG";
	else
		newPair.first = gst_value_serialize(format);

	capsRecord.height = gst_structure_id_get_value (structure, m_height)->data->v_int;
	capsRecord.width = gst_structure_id_get_value (structure, m_width)->data->v_int;
	auto it = capsSet.find(capsRecord);
	if(it != capsSet.end())
	{
		capsRecord = *it;
		capsSet.erase(it);
	}

	auto it2 = capsRecord.videoFormats.find(newPair.first);
	if(it2 != capsRecord.videoFormats.end())
	{
		newPair = *it2;
		capsRecord.videoFormats.erase(it2);
	}

	for(unsigned int i=0; i < gst_value_list_get_size (framerates); ++i)
	{
		const GValue* fract = gst_value_list_get_value(framerates, i);
		const gchar* serializedFract = gst_value_serialize(fract);

		newPair.second.insert(serializedFract);
	}

	capsRecord.videoFormats.insert(newPair);
	capsSet.insert(capsRecord);
}

bool V4LCameraDetector::IsSupportedStructureFormat(const GstStructure* structure) const
{
	bool isAcceptable = (gst_structure_get_name_id(structure) == m_videoXRaw) ? true : false;
	isAcceptable |= (gst_structure_get_name_id(structure) == m_videoMPEG) ? true : false;

	return isAcceptable;
}

void V4LCameraDetector::CapabilitiesDetectionWorkLog(const GstElement* camera, const std::set<CameraCapsRecord>& capsSet) const
{
	std::stringstream log;
	log << "\tDetected following supported camera capabilities: \n";

	for(auto record : capsSet)
	{
		log << "\t Width: " << record.width << " Height: " << record.height << "\n";
		for(auto format : record.videoFormats)
		{
			log << "\t  Format: " << format.first << " with framerates: ";
			for(auto framerate : format.second)
			{
				log << framerate << " ";
			}
			log << "\n";
		}
	}

	m_context->Logger->WriteInfo(log.str());
}

V4LCameraDetector::~V4LCameraDetector()
{
}

GQuark V4LCameraDetector::m_format = g_quark_from_static_string("format");
GQuark V4LCameraDetector::m_width = g_quark_from_static_string("width");
GQuark V4LCameraDetector::m_height = g_quark_from_static_string("height");
GQuark V4LCameraDetector::m_pixel_aspect_ratio = g_quark_from_static_string("pixel-aspect-ratio");
GQuark V4LCameraDetector::m_interlance_mode = g_quark_from_static_string("interlace-mode");
GQuark V4LCameraDetector::m_framerate = g_quark_from_static_string("framerate");
GQuark V4LCameraDetector::m_videoXRaw = g_quark_from_static_string("video/x-raw");
GQuark V4LCameraDetector::m_videoMPEG = g_quark_from_static_string("image/jpeg");
