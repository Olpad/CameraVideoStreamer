/**
 * @class CameraHandler
 * 
 * @brief Responsible for everything, like a typical manager, right?
 * 	This class uses other classes to give using camera in the application
 * 	a common interface.
 *
 * @date Aug 21, 2014
 * @author Aleksander Bulski
 */

#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include "../Exceptions/NoCamerasDetectedException.h"
#include "V4LCameraDetector.h"
#include "V4LCameraDevice.h"
#include <list>
#include <memory>

class CameraHandler
{
public:
	CameraHandler(Context* context);

	void Initialize();

	virtual ~CameraHandler();

private:
	Context* m_context;
	std::list<std::shared_ptr<ICameraDevice>> m_cameraDevices;
	std::shared_ptr<ICameraDetector> m_cameraDetector;
};

#endif /* CAMERAMANAGER_H_ */
