/**
 * @class BasicCameraHandler
 * 
 * @brief Responsible for everything, like a typical manager, right?
 * 	This class uses other classes to give using camera in the application
 * 	a common interface.
 *
 * @date Aug 21, 2014
 * @author Aleksander Bulski
 */

#ifndef BASICCAMERAHANDLER_H_
#define BASICCAMERAHANDLER_H_

#include <list>
#include <memory>
#include "ICameraHandler.h"
#include "V4LCameraDetector.h"
#include "V4LCameraDevice.h"
#include "../Context.h"

class BasicCameraHandler : public ICameraHandler
{
public:
	BasicCameraHandler(Context* context);

	void Initialize();

	std::shared_ptr<IStreamElement> GetCameraElement(const std::string& systemPath) override;

	const std::map<CameraPath, CameraName>& GetCameras() const override;

	unsigned char GetNumOfCameras() const override;

	virtual ~BasicCameraHandler();

private:
	Context* m_context;
	std::list<std::shared_ptr<ICameraDevice>> m_cameraDevices;
	std::shared_ptr<ICameraDetector> m_cameraDetector;
};

#endif /* BASICCAMERAHANDLER_H_ */
