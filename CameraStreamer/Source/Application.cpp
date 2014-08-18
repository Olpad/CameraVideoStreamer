#include "Application.h"

Application::Application()
{
	m_context = new Context();
	try
	{
		m_context->ConfigurationReader = new BasicINIConfigReader();
		m_context->ConfigurationReader->Initialize();
		m_context->Logger = new BasicTxtLogger(m_context);
		m_context->Logger->Initialize();
		m_context->Logger->WriteInfo("Late information: configuration loaded correctly.");
	}
	catch(...)
	{
		std::cout << "[CRITICAL ERROR] Application services couldn't be initialized properly" << std::endl;
	}
}

Application::~Application()
{
	if(m_context->Logger == nullptr)
	{
		std::cout << "EMERGENCY application exit" << std::endl;
	}
	else
	{
		std::cout << "Standard application exit." << std::endl;
		m_context->Logger->WriteInfo("Standard application exit.");
	}

	delete m_context;
}
