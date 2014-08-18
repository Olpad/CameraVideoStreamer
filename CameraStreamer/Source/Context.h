/**
 * \struct Context
 * \brief Object storing all the main services necessary for frequent access.
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
		if(ConfigurationReader != nullptr)
			delete ConfigurationReader;

		if(Logger != nullptr)
			delete Logger;
	}
};

#endif /* CONTEXT_H_ */
