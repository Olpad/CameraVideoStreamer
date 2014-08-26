/**
 * @interface ICameraHandler
 *
 * @brief Represents common functionality implemented by camera
 * 	handlers.
 *
 * @date Aug 25, 2014
 * @author Aleksander Bulski
 */


#ifndef ICAMERAHANDLER_H_
#define ICAMERAHANDLER_H_

#include <map>
#include "ICameraDetector.h"
#include "../ISystemService.h"
#include "../MediaStream/IStreamElement.h"
#include "../Exceptions/NoCamerasDetectedException.h"

class ICameraHandler : public ISystemService
{
public:
	/**
	 * @brief Fetches camera element ready to be used in a stream.
	 * @param[in] systemPath Cameras system path.
	 * @return Pointer to the stream element object or nullptr if invalid path.
	 */
	virtual std::shared_ptr<IStreamElement> GetCameraElement(const std::string& systemPath) = 0;

	/**
	 * @brief Fetches names and system paths of all detected cameras.
	 * @return Map of names and system paths.
	 */
	virtual const std::map<CameraPath, CameraName>& GetCameras() const = 0;

	/**
	 * @brief Gets number of detected cameras.
	 * @return Number of detected cameras.
	 */
	virtual unsigned char GetNumOfCameras() const = 0;

	virtual ~ICameraHandler() {}
};

#endif /* ICAMERAHANDLER_H */
