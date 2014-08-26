#include "BasicMediaStream.h"

BasicMediaStream::BasicMediaStream(unsigned int streamID, Context* context)
	: m_id(streamID), m_context(context), m_pipeline(nullptr), m_bus(nullptr),
	  m_stream(nullptr)
{
}

void BasicMediaStream::Create()
{

}

bool BasicMediaStream::SetState(GstState newState)
{
	if(m_pipeline == nullptr)
		return false;

	return gst_element_set_state(m_pipeline, newState);
}

unsigned int BasicMediaStream::GetID() const
{
	return m_id;
}

BasicMediaStream::~BasicMediaStream()
{
}

