#include "Application.h"

Application::Application()
{
   gst_init (0, 0);
	//PreInitializeApp();

	m_context = new Context();
	try
	{
		m_context->ConfigurationReader = new BasicINIConfigReader();
		m_context->ConfigurationReader->Initialize();
		m_context->Logger = new BasicTxtLogger(m_context);
		m_context->Logger->Initialize();
		m_context->Logger->WriteInfo("Late information: configuration loaded correctly.");
		m_context->Logger->WriteInfo("Late information: logger initialized.");
		m_context->CameraHandler = new BasicCameraHandler(m_context);
		m_context->CameraHandler->Initialize();
		m_context->Logger->WriteInfo("Camera handler initialized.");
		m_context->StreamManager = new BasicStreamManager(m_context);
		m_context->StreamManager->Initialize();

		//test
		bool result = m_context->StreamManager->SetStateOfStream(GST_STATE_PLAYING, "testStream");
		if(result)
		{
			GMainLoop *main_loop = g_main_loop_new (NULL, FALSE);
			g_main_loop_run (main_loop);
		}
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

void Application::PreInitializeApp()
{
   gst_init (0, 0);
}
