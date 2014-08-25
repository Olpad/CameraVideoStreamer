#include "V4LCameraDevice.h"

V4LCameraDevice::V4LCameraDevice(const std::string& deviceName, const std::string& systemPath)
	: StreamElement("v4l2src", systemPath.c_str()), m_deviceName(deviceName),
	  m_systemPath(systemPath), m_type(Source)
{
	//set constant parameters
	g_object_set(m_element, "device", systemPath.c_str(), NULL);
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
	return true;
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

StreamElementType V4LCameraDevice::GetType() const
{
	return m_type;
}

V4LCameraDevice::~V4LCameraDevice()
{
}

void V4LCameraDevice::InitializeValueTypes()
{
}
