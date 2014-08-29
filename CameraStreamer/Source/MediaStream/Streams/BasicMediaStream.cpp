#include "BasicMediaStream.h"
#include <sstream>

BasicMediaStream::BasicMediaStream(const std::string& name, Context* context)
	: MediaStream(name), m_context(context)
{
}

void BasicMediaStream::Create()
{
	std::string defaultCameraPath =
			m_context->ConfigurationReader->GetKeyStringValue(KnownConfigKeys::BMS_DEFAULT_CAMERA);

	// setting source
	auto availableCameras = m_context->CameraHandler->GetCameras();
	auto it = availableCameras.find(defaultCameraPath);
	if(it == availableCameras.end())
		return;
	auto cameraElement = m_context->CameraHandler->GetCameraElement(defaultCameraPath);
	m_elements.push_back(cameraElement);

	/*
	// setting queue
	std::string queueName = "queue";
	std::shared_ptr<IStreamElement> queueElement = std::make_shared<QueueElement>(queueName);
	m_elements.push_back(queueElement);
	*/

	// setting MPEG decode stream
	std::string mpegDecode = "decodebin";
	std::shared_ptr<IStreamElement> decodeElement = std::make_shared<DecodeBinElement>(mpegDecode);
	m_elements.push_back(decodeElement);

	// setting sink
	std::string sinkName = "sink";
	std::shared_ptr<IStreamElement> sinkElement = std::make_shared<AutoVideoSinkElement>(sinkName);
	m_elements.push_back(sinkElement);

	if(cameraElement == nullptr //|| queueElement == nullptr
			|| decodeElement == nullptr || sinkElement == nullptr)
	{
		const std::string errorMsg = "Couldn't create elements in stream: " + m_name;
		m_context->Logger->WriteError(errorMsg);
		throw StreamNotCreatedException(m_name);
	}

	// adding elements to stream
	bool success = true;

	success &= cameraElement->AddToStream(m_bin);
	//success &= queueElement->AddToStream(m_bin);
	//success &= decodeElement->AddToStream(m_bin);
	success &= sinkElement->AddToStream(m_bin);

	if(!success)
	{
		const std::string errorMsg = "Couldn't add elements to stream: " + m_name;
		m_context->Logger->WriteError(errorMsg);
		throw StreamNotCreatedException(m_name);
	}

	//success &= cameraElement->LinkElement(decodeElement);
	//success &= decodeElement->LinkElement(sinkElement);
	//std::map<std::string, std::string> params = {{"height", "640"}, {"width", "480"}, {"framerate", "30/1"}};
	success &= cameraElement->LinkElement(sinkElement);

	g_object_set (sinkElement->GetRawElement(), "sync", false, NULL);
	if(!success)
	{
		const std::string errorMsg = "Couldn't link elements in stream: " + m_name;
		m_context->Logger->WriteError(errorMsg);
		throw StreamNotCreatedException(m_name);
	}
}

BasicMediaStream::~BasicMediaStream()
{
}

int BasicMediaStream::ProcessBusMessage(GstBus* bus, GstMessage* message,
		gpointer user_data)
{
	switch (GST_MESSAGE_TYPE (message))
	{
	    case GST_MESSAGE_ERROR:
	    {
	      GError *err;
	      gchar *debug;

	      gst_message_parse_error (message, &err, &debug);

	      std::string errorMsg = "Stream " + m_name + " encountered an error: " + err->message;
	      m_context->Logger->WriteError(errorMsg);

	      g_error_free (err);
	      g_free (debug);

	      gst_element_set_state (m_pipeline, GST_STATE_READY);
	      gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
	      break;
	    }

	    case GST_MESSAGE_EOS:
	    {
	      gst_element_set_state (m_pipeline, GST_STATE_READY);

	      std::string info = "Stream " + m_name + " was stopped.";
	      m_context->Logger->WriteInfo(info);
	      break;
	    }

	      /*// REMARK: code based on GStreamer tutorial
	    case GST_MESSAGE_BUFFERING:
	      gint percent = 0;

	      // disable buffering when in playing mode
	      if (m_pipeline->pending_state == GST_STATE_PLAYING)
	      	break;

	      if (percent < 100)
	        gst_element_set_state (m_pipeline, GST_STATE_PAUSED);
	      else
	        gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
	      break;
	       */

	    case GST_MESSAGE_CLOCK_LOST:
	    {
	   	std::string warn = "Stream " + m_name + " lost clock. Reseting.";
		   m_context->Logger->WriteWarning(warn);

		   gst_element_set_state (m_pipeline, GST_STATE_PAUSED);
	      gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
	      break;
	    }

	    case GST_MESSAGE_STATE_CHANGED:
	    {
	   	GstState oldState, newState, pendingState;
	   	gst_message_parse_state_changed (message, &oldState, &newState, &pendingState);
	   	std::stringstream msg;
		   msg << "Stream " << m_name << " changed state from "
		   		<< gst_element_state_get_name (oldState) << " to "
		   		<< gst_element_state_get_name (newState) << ", pending: "
		   		<< gst_element_state_get_name (pendingState);
			m_context->Logger->WriteWarning(msg.str());
			break;
	    }

	    default:
	    {
	   	std::stringstream msg;
	   	msg << "Unhandled message: ";
	   	msg << gst_message_type_get_name(GST_MESSAGE_TYPE (message));
			m_context->Logger->WriteWarning(msg.str());
	      break;
	    }
	 }

	return 1;
}
