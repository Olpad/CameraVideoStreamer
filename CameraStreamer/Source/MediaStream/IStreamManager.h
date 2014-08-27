/**
 * @class IStreamManager
 * 
 * @brief Stream manager common interface.
 *
 * @date Aug 27, 2014
 * @author Aleksander Bulski
 */

#ifndef ISTREAMMANAGER_H_
#define ISTREAMMANAGER_H_

#include "gst/gst.h"
#include "../ISystemService.h"

class IStreamManager : public ISystemService
{
public:
	virtual unsigned int GetNumberOfStreams() const = 0;

	virtual bool SetStateOfStream(GstState state, const std::string& streamName) = 0;

	virtual ~IStreamManager() {}
};

#endif /* ISTREAMMANAGER_H_ */
