#include "BasicCameraHandler.h"

BasicCameraHandler::BasicCameraHandler(Context* context)
{
	m_context = context;
	m_cameraDetector = std::make_shared<V4LCameraDetector>(context);
}

void BasicCameraHandler::Initialize()
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
		std::shared_ptr<V4LCameraDevice> newCamera = std::make_shared<V4LCameraDevice>(camera.second, camera.first);

		auto capsSet = m_cameraDetector->DetectCapabilities(camera.first);
		newCamera->AddCapabilities(capsSet);

		m_cameraDevices.push_back(newCamera);
	}
}

std::shared_ptr<IStreamElement> BasicCameraHandler::GetCameraElement(
		const std::string& systemPath)
{
	for(auto camera : m_cameraDevices)
	{
		if(camera->GetName() == systemPath)
		{
			std::shared_ptr<IStreamElement> cameraElement = std::dynamic_pointer_cast<IStreamElement>(camera);
			return cameraElement;
		}
	}

	return std::shared_ptr<IStreamElement>();
}

const std::map<CameraPath, CameraName>& BasicCameraHandler::GetCameras() const
{
	return m_cameraDetector->GetDetectedCameras();
}

unsigned char BasicCameraHandler::GetNumOfCameras() const
{
	return m_cameraDevices.size();
}

BasicCameraHandler::~BasicCameraHandler()
{
}
