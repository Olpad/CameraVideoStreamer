/**
 * @class V4LCameraDevice
 * 
 * @brief Hold data of a valid Video4Linux compliant camera connected to the system.
 *
 * @date Aug 20, 2014
 * @author Aleksander Bulski
 */

#ifndef CAMERADEVICE_H_
#define CAMERADEVICE_H_

#include "ICameraDevice.h"
#include "../MediaStream/StreamElement.h"

class V4LCameraDevice : public ICameraDevice, public StreamElement
{
public:
	V4LCameraDevice(const std::string& deviceName, const std::string& systemPath);

	const std::string& GetName() const override;

	const std::string& GetSystemPath() const override;

	const std::set<CameraCapsRecord>& GetCapabilities() const override;

	StreamElementType GetType() const override;

	bool IsAValidSource() const override;

	void AddCapability(CameraCapsRecord& newCaps) override;

	void AddCapabilities(std::set<CameraCapsRecord> capsSet);

	virtual ~V4LCameraDevice();

protected:
	const std::string m_deviceName;
	const std::string m_systemPath;
	StreamElementType m_type;
	std::set<CameraCapsRecord> m_capabilities;

	void InitializeValueTypes() override;
};

#endif /* CAMERADEVICE_H_ */
