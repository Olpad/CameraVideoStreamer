#include "MediaStream.h"

MediaStream::MediaStream(const std::string& name) : m_name(name)
{
	m_pipeline = gst_pipeline_new(name.c_str());

	m_bus = gst_pipeline_get_bus(GST_PIPELINE(m_pipeline));
	gst_bus_add_watch(m_bus, ProcessBusMessageWrapper, this);

	m_bin = GST_BIN(m_pipeline);
}

bool MediaStream::SetState(GstState newState)
{
	if(m_pipeline == nullptr)
		return false;

	return gst_element_set_state(m_pipeline, newState);
}

void MediaStream::Restart()
{
   gst_element_set_state (m_pipeline, GST_STATE_READY);
   gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
}

const std::string& MediaStream::GetName() const
{
	return m_name;
}

MediaStream::~MediaStream()
{
	gst_object_unref(GST_OBJECT(m_bin));
	gst_object_unref(GST_OBJECT(m_bus));
	gst_object_unref(GST_OBJECT(m_pipeline));
}

int MediaStream::ProcessBusMessageWrapper(GstBus* bus, GstMessage* message,
		gpointer user_data)
{
	MediaStream* instance = (MediaStream*)user_data;
	return instance->ProcessBusMessage(bus, message, user_data);
}
