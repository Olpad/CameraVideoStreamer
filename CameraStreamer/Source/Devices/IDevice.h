/**
 * @interface IDevice
 * 
 * @brief Functions common to all devices.
 *
 * @date Aug 20, 2014
 * @author Aleksander Bulski
 */

#ifndef IDEVICE_H_
#define IDEVICE_H_

#include <string>

class IDevice
{
public:
	/**
	 * @brief Gets a name of the device as it is stated by the system driver.
	 * @return System name of the device.
	 */
	virtual const std::string& GetName() const = 0;

	/**
	 * @brief Gets a system path to the device.
	 * @return Path to the device in the system.
	 */
	virtual const std::string& GetSystemPath() const = 0;

	/**
	 * @brief Checks if a device can be a valid source.
	 * @return True if device can be a valid source.
	 */
	virtual bool IsAValidSource() const = 0;

	virtual ~IDevice() {}
};

#endif /* IDEVICE_H_ */
