/**
 * @class ICameraDevice
 * 
 * @brief Interface to access generic camera device.
 *
 * @date Aug 21, 2014
 * @author Aleksander Bulski
 */

#ifndef ICAMERADEVICE_H_
#define ICAMERADEVICE_H_

#include "IDevice.h"
#include "CameraCapsRecord.h"

class ICameraDevice : public IDevice
{
public:
	virtual const std::set<CameraCapsRecord>& GetCapabilities() const = 0;

	virtual void AddCapability(CameraCapsRecord& newCaps) = 0;

	virtual ~ICameraDevice() {};
};

#endif /* ICAMERADEVICE_H_ */
