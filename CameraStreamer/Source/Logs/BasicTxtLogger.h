/**
 * @class BasicTxtLogger
 * 
 * @brief Class used to write logs as separate .txt files
 *  under a path specified by configuration file. Maximum
 *  number of logs is also specified mentioned file.
 *
 * @date Aug 18, 2014
 * @author Aleksander Bulski
 */

#ifndef BASICTXTLOGGER_H_
#define BASICTXTLOGGER_H_

#include "boost/filesystem.hpp"
#include <ctime>
#include <iostream>
#include <fstream>
#include "../Context.h"
#include "../Configuration/KnownConfigKeys.h"

class BasicTxtLogger: public ILogger
{
public:
	BasicTxtLogger(Context *context) : m_context(context), m_maxNumOfLogFiles(0)
	{	}

	void Initialize() override;

	void WriteInfo(const std::string& msg) override;

	void WriteWarning(const std::string& msg) override;

	void WriteError(const std::string& msg) override;

	virtual ~BasicTxtLogger();

private:
	Context* m_context;
	std::string m_dirPath;
	int m_maxNumOfLogFiles;
	std::ofstream m_log;

	const std::string TEMPLATE_INFO = "[INFO] ";
	const std::string TEMPLATE_WARNING = "[WARNING] ";
	const std::string TEMPLATE_ERROR = "[ERROR] ";
	const std::string TEMPLATE_LOG_NAME_HEADER = "CSLog_";
	const std::string TEMPLATE_LOG_NAME_EXTENSION = ".txt";

	/**
	 * @brief Loads configuration keys.
	 * @exception Throws when the configuration cannot be loaded.
	 */
	void LoadConfiguration();

	/**
	 * @brief Checks if directory exists and creates it otherwise.
	 * @exception Throws when the directory cannot be created.
	 */
	void ValidateDirectory();

	/**
	 * @brief Read all logs and deletes excessive amount.
	 * @todo Implement validation
	 */
	void CleanLogs();

	/**
	 * @brief Creates a new log file in the given path.
	 */
	void CreateNewLogFile();
};

#endif /* BASICTXTLOGGER_H_ */
