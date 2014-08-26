#include "MediaStream.h"

MediaStream::MediaStream(unsigned int streamID) :
		m_id(streamID), m_pipeline(nullptr), m_bus(nullptr), m_stream(nullptr)
{
}

bool MediaStream::SetState(GstState newState)
{
	if(m_pipeline == nullptr)
		return false;

	return gst_element_set_state(m_pipeline, newState);
}

unsigned int MediaStream::GetID() const
{
	return m_id;
}

MediaStream::~MediaStream()
{
}
