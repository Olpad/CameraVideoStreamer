/**
 * @struct Context
 * @brief Object storing all the main services necessary for frequent access.
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "./Configuration/IConfigurationReader.h"
#include "./Logs/ILogger.h"

struct Context
{
	Context() : ConfigurationReader(nullptr), Logger(nullptr)
	{	}

	IConfigurationReader* ConfigurationReader;
	ILogger* Logger;

	~Context()
	{
		if(Logger != nullptr)
		{
			delete Logger;
			Logger = nullptr;
		}

		if(ConfigurationReader != nullptr)
		{
			delete ConfigurationReader;
			ConfigurationReader = nullptr;
		}
	}
};

#endif /* CONTEXT_H_ */
