#include "BasicMediaStream.h"

BasicMediaStream::BasicMediaStream(const std::string& name, Context* context)
	: MediaStream(name), m_context(context)
{
}

void BasicMediaStream::Create()
{
	// setting source
	auto availableCameras = m_context->CameraHandler->GetCameras();
	const std::string& cameraPath = availableCameras.rbegin()->first;
	auto cameraElement = m_context->CameraHandler->GetCameraElement(cameraPath);

	// setting queue
	std::string queueName = "queue";
	std::shared_ptr<IStreamElement> queueElement = std::make_shared<QueueElement>(queueName);

	// setting sink
	std::string sinkName = m_name + "sink";
	std::shared_ptr<IStreamElement> sinkElement = std::make_shared<AutoVideoSinkElement>(sinkName);

	if(cameraElement == nullptr || queueElement == nullptr || sinkElement == nullptr)
	{
		const std::string errorMsg = "Couldn't create elements in stream: " + m_name;
		m_context->Logger->WriteError(errorMsg);
		throw StreamNotCreatedException(m_name);
	}

	// adding elements to stream
	bool success = true;
	success &= cameraElement->AddToStream(m_bin);
	success &= queueElement->AddToStream(m_bin);
	success &= sinkElement->AddToStream(m_bin);

	if(!success)
	{
		const std::string errorMsg = "Couldn't add elements to stream: " + m_name;
		m_context->Logger->WriteError(errorMsg);
		throw StreamNotCreatedException(m_name);
	}

	success &= cameraElement->LinkElement(queueElement);
	success &= queueElement->LinkElement(sinkElement);

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
	      gst_element_set_state (m_pipeline, GST_STATE_READY);
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

	    default:
	      break;
	 }

	return 1;
}
