#include "V4LCameraDetector.h"
#include "boost/filesystem.hpp"
#include <streambuf>
#include <fstream>
#include <sstream>
#include "../Exceptions/ConfigRecordReadFailedException.h"
#include "../Configuration/KnownConfigKeys.h"

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
   DetermineCapabilities(camera);

   gst_element_set_state (pipeline, GST_STATE_NULL);
   gst_object_unref (pipeline);

   return capsRecords;
}

void V4LCameraDetector::DetermineCapabilities(GstElement* camera)
{
   // retrieve pad and caps
   GstPad* pad = gst_element_get_static_pad(camera, "src");
   GstCaps* caps = gst_pad_query_caps(pad, NULL);

   // validate caps
   if(caps == NULL)
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - Querying NULL camera capabilities.");
   }

   if(gst_caps_is_any(caps))
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - Found an error or a camera with ANY capabilities. The second is kind of unlikely.");
   }

   if(gst_caps_is_empty(caps))
   {
   	m_context->Logger->WriteError("CameraDetector::DetectCapabilities - Found a camera with EMPTY capabilities.");
   }

   // parse all capabilities
   GstStructure *structure = NULL;
   for(uint i=0; i < gst_caps_get_size(caps); ++i)
   {
   	structure = gst_caps_get_structure(caps, i);

   	if(structure == NULL)
   		continue;

   	gst_structure_foreach(structure, ForEachCapabilityParser, NULL);
   }
}

V4LCameraDetector::~V4LCameraDetector()
{
}

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

gboolean V4LCameraDetector::ForEachCapabilityParser(GQuark field,
	const GValue* value, gpointer pfx)
{
	  const gchar *val = gst_value_serialize (value);
	  const gchar *key = g_quark_to_string (field);

	  std::cout << (char*)value->data->v_pointer << " " << val << " " << key << std::endl;

	  return true;
}
