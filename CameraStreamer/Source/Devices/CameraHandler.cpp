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

	// process all available cameras
	for(auto camera : availableCameras)
	{
		std::shared_ptr<V4LCameraDevice> newCamera = std::make_shared<V4LCameraDevice>(camera.second, camera.first, true);

		auto capsSet = m_cameraDetector->DetectCapabilities(camera.first);
		newCamera->AddCapabilities(capsSet);

		m_cameraDevices.push_back(newCamera);
	}
}

CameraHandler::~CameraHandler()
{
}
