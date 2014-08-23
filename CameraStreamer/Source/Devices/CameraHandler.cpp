#include "CameraHandler.h"

CameraHandler::CameraHandler(Context* context)
{
	m_context = context;
	m_cameraDetector = std::make_shared<V4LCameraDetector>(context);
}

void CameraHandler::Initialize()
{
	auto availableCameras = m_cameraDetector->DetectSystemCameras();
	if(availableCameras.size() == 0)
	{
		m_context->Logger->WriteError("CRITICAL - no cameras present. Closing the application.");
		throw NoCamerasDetectedException();
	}

	for(auto camera : availableCameras)
	{
		// todo create cameradevice
		m_cameraDetector->DetectCapabilities(camera.first);
	}
}

CameraHandler::~CameraHandler()
{
	// TODO Auto-generated destructor stub
}
