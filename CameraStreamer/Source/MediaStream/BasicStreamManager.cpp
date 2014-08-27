#include "BasicStreamManager.h"

BasicStreamManager::BasicStreamManager(Context* context)
{
	m_context = context;
}

void BasicStreamManager::Initialize()
{
	// setting up test stream with arbitrary ID = name
	auto stream = std::make_shared<BasicMediaStream>(std::string("testStream"), m_context);
	stream->Create();
	m_streams.insert(std::make_pair("testStream", stream));
}

unsigned int BasicStreamManager::GetNumberOfStreams() const
{
	return m_streams.size();
}

bool BasicStreamManager::SetStateOfStream(GstState state, const std::string& streamName)
{
	auto it = m_streams.find(streamName);
	if(it == m_streams.end())
		return false;

	return it->second->SetState(state);
}


BasicStreamManager::~BasicStreamManager()
{
}

