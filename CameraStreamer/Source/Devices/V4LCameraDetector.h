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

	void DetermineCapabilities(GstElement* camera, std::set<CameraCapsRecord>& capsSet);

	bool IsAcceptableStructure(const GstStructure* structure) const;

	static gboolean ForEachCapabilityParser(GQuark field, const GValue * value, gpointer capsRecord);
};

#endif /* CAMERADETECTOR_H_ */
