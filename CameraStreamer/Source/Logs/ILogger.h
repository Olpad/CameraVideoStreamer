/**
 * @interface ILogger
 * @brief Interface to implement by every logging class.
 */

#ifndef ILOGGER_H_
#define ILOGGER_H_

#include <string>
#include "../ISystemService.h"

class ILogger : public ISystemService
{
public:
	/*
	 *	@brief Initializes class.
	 */
	virtual void Initialize() = 0;

	/**
	 * Logs a standard message containing information.
	 * @param[in] msg Message to write.
	 */
	virtual void WriteInfo(const std::string& msg) = 0;

	/**
	 * Logs a standard message containing warning.
	 * @param[in] msg Message to write.
	 */
	virtual void WriteWarning(const std::string& msg) = 0;

	/**
	 * Logs a standard message containing error.
	 * @param[in] msg Message to write.
	 */
	virtual void WriteError(const std::string& msg) = 0;

	virtual ~ILogger() {}
};

#endif /* ILOGGER_H_ */
