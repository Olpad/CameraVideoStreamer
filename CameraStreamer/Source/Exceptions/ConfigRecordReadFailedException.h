/**
 * @class ConfigRecordReadFailedException
 * 
 * @brief Exception to be thrown on configuration key/value read failure.
 *
 * @date Aug 21, 2014
 * @author Aleksander Bulski
 */

#ifndef CONFIGRECORDREADFAILEDEXCEPTION_H_
#define CONFIGRECORDREADFAILEDEXCEPTION_H_

#include <string>
#include <stdexcept>

class ConfigRecordReadFailedException : public std::runtime_error
{
public:
	ConfigRecordReadFailedException(const std::string& key)
			: std::runtime_error(std::string("Searching for key: " + key + " failed"))
		{	}

};

#endif /* CONFIGRECORDREADFAILEDEXCEPTION_H_ */
