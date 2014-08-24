#include "V4LCameraDevice.h"

V4LCameraDevice::V4LCameraDevice(const std::string& deviceName, const std::string& systemPath, bool isAValidSource)
	: m_deviceName(deviceName), m_systemPath(systemPath), m_isValidSource(isAValidSource)
{
}

const std::string& V4LCameraDevice::GetName() const
{
	return m_deviceName;
}

const std::string& V4LCameraDevice::GetSystemPath() const
{
	return m_systemPath;
}

bool V4LCameraDevice::IsAValidSource() const
{
	// todo
	return m_isValidSource;
}

const std::set<CameraCapsRecord>& V4LCameraDevice::GetCapabilities() const
{
	return m_capabilities;
}

void V4LCameraDevice::AddCapability(CameraCapsRecord& newCaps)
{
	m_capabilities.insert(newCaps);
}

void V4LCameraDevice::AddCapabilities(std::set<CameraCapsRecord> capsSet)
{
	m_capabilities.insert(capsSet.begin(), capsSet.end());
}

V4LCameraDevice::~V4LCameraDevice()
{
}

