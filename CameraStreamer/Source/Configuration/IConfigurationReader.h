/**
 * @interface IConfigurationReader
 * @brief Base interface for a configuration reading module.
 */

#ifndef ICONFIGURATIONREADER_H_
#define ICONFIGURATIONREADER_H_

#include <string>

class IConfigurationReader
{
public:
	/**
	 * \brief Used to initialize and (most likely) load the configuration data.
	 */
	virtual void Initialize() = 0;
	
	/**
	 * @param[in] sKeyName Name of the key in the configuration file.
	 * @return Value of the key as an int.
	 * @exception Throws when key was not found.
	 */
	virtual int GetKeyIntValue(const std::string& sKeyName) = 0;

	/**
	 * @param[in] sKeyName Name of the key in the configuration file.
	 * @return Value of the key as an int or -1.
	 * @exception No exceptions are thrown by this method.
	 */
	virtual int TryGetKeyIntValue(const std::string& sKeyName) = 0;

	/**
	 * @param[in] sKeyName Name of the key in the configuration file.
	 * @return Value of the key as a string.
	 * @exception Throws when key was not found.
	 */
	virtual std::string GetKeyStringValue(const std::string& sKeyName) = 0;

	/**
	 * @param[in] sKeyName Name of the key in the configuration file.
	 * @return Value of the key as a string or "".
	 * @exception No exceptions are thrown by this method.
	 */
	virtual std::string TryGetKeyStringValue(const std::string& sKeyName) = 0;

	virtual ~IConfigurationReader() {};
};

#endif /* ICONFIGURATIONREADER_H_ */
