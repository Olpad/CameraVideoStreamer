/**
 * @interface ICameraDetector
 * 
 * @brief CameraDetector class general functions.
 *
 * @date Aug 21, 2014
 * @author Aleksander Bulski
 */

#ifndef ICAMERADETECTOR_H_
#define ICAMERADETECTOR_H_

#include <map>
#include <set>
#include <iostream>
#include <gst/gst.h>
#include "CameraCapsRecord.h"

typedef std::string CameraName,
						  CameraPath;

class ICameraDetector
{
public:
	/**
	 * @brief Detects all video4linux compliant cameras.
	 * @return Map of detected camera paths and camera names.
	 */
	virtual const std::map<CameraPath, CameraName>& DetectSystemCameras() = 0;

	/**
	 * @brief Returns all video4linux compliant cameras.
	 * @return Map of detected camera paths and camera names.
	 */
	virtual const std::map<CameraPath, CameraName>& GetDetectedCameras() const = 0;

	/**
	 * @brief Checks if camera is capable of streaming.
	 * @param[in] systemPath System path to camera.
	 * @return Information if camera is valid for streaming.
	 */
	virtual bool ValidateCamera(const std::string& systemPath) = 0;

	/**
	 * @brief Determines all possible streaming parameters of camera.
	 * @param[in] systemPath System path to camera.
	 * @return Set of capabilities of the camera found under the path.
	 */
	virtual std::set<CameraCapsRecord> DetectCapabilities(const std::string& systemPath) = 0;

	virtual ~ICameraDetector() {}
};

#endif /* ICAMERADETECTOR_H_ */
