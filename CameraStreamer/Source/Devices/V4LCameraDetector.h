/**
 * @class V4LCameraDetector
 * 
 * @brief Responsible for finding all video4linux cameras available
 * 	in the system and determining their capabilities.
 *
 * @date Aug 19, 2014
 * @author Aleksander Bulski
 */

#ifndef CAMERADETECTOR_H_
#define CAMERADETECTOR_H_

#include "ICameraDetector.h"
#include "../Context.h"

class V4LCameraDetector : public ICameraDetector
{
public:
	V4LCameraDetector(Context* context);

	/**
	 * @brief Detects all video4linux compliant cameras.
	 * @return Map of detected camera paths and camera names.
	 */
	const std::map<CameraPath, CameraName>& DetectSystemCameras() override;

	/**
	 * @brief Returns all video4linux compliant cameras.
	 * @return Map of detected camera paths and camera names.
	 */
	const std::map<CameraPath, CameraName>& GetDetectedCameras() const override;

	/**
	 * @brief Checks if camera is capable of streaming.
	 * @param[in] systemPath System path to camera.
	 * @return Information if camera is valid for streaming.
	 */
	bool ValidateCamera(const std::string& systemPath) override;

	/**
	 * @brief Determines all possible streaming parameters of camera.
	 * @param[in] systemPath System path to camera.
	 * @return Set of capabilities of the camera found under the path.
	 */
	std::set<CameraCapsRecord> DetectCapabilities(const std::string& systemPath) override;

	virtual ~V4LCameraDetector();

protected:
	Context* m_context;
	std::string m_pathToV4lDir;
	std::map<CameraPath, CameraName> m_detectedCameras;
	const std::string DEFAULT_V4L_PATH = "/sys/class/video4linux";

	/* values below are set only once to make comparisons faster */
	static GQuark m_format;
	static GQuark m_width;
	static GQuark m_height;
	static GQuark m_pixel_aspect_ratio;
	static GQuark m_interlance_mode;
	static GQuark m_framerate;

	static GQuark m_videoXRaw;
	static GQuark m_videoMPEG;

	/**
	 * @brief Organizes a sequence of actions for obtaining camera data.
	 * @param[in] camera Camera in ready/pause/playing state.
	 * @param[out] capsSet Empty set to fill with new capabilities.
	 */
	void FetchCapabilities(GstElement* camera, std::set<CameraCapsRecord>& capsSet);

	/**
	 * @brief Validates caps object. Logs errors.
	 * @param[in] caps Caps object to validate.
	 * @return True if caps object is valid.
	 */
	bool IsAValidCaps(GstCaps* caps) const;

	/**
	 * @brief Validate structure object and formats. Logs errors.
	 * @param[in] structure Structure to validate.
	 * @return True if structure object is valid.
	 */
	bool IsAValidStructure(GstStructure *structure) const;

	/**
	 * @brief Scans structure for useful data and serializes it into a single
	 *  CameraCapsRecord	structure.
	 * @param[in] structure Structure containing parameters.
	 * @param[out] capsSet Set of camera records to store new camera record into.
	 */
	void AddNewCapability(GstStructure *structure, std::set<CameraCapsRecord>& capsSet);

	/**
	 * @brief Checks if application is capable of supporting given format.
	 * @param[in] structure Structure with format data.
	 * @return True if data in a structure descibes a supported format.
	 */
	bool IsSupportedStructureFormat(const GstStructure* structure) const;

	/**
	 * @brief Logs results of the capability search.
	 * @param[in] camera Camera which the search was performed for.
	 * @param[in] capsSet Set of resulting records.
	 */
	void CapabilitiesDetectionWorkLog(const GstElement* camera, const std::set<CameraCapsRecord>& capsSet) const;
};

#endif /* CAMERADETECTOR_H_ */
