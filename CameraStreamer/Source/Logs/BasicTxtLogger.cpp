#include "BasicTxtLogger.h"


void BasicTxtLogger::Initialize()
{
	LoadConfiguration();
	ValidateDirectory();
	CleanLogs();
	CreateNewLogFile();

	WriteInfo("New log created.");
}

void BasicTxtLogger::LoadConfiguration()
{
	IConfigurationReader* conf = m_context->ConfigurationReader;

	try
	{
		m_dirPath = conf->GetKeyStringValue(KnownConfigKeys::PATH_TO_LOGS);
		m_maxNumOfLogFiles = conf->GetKeyIntValue(KnownConfigKeys::MAX_NUMBER_OF_LOG_FILES);
	}
	catch (std::exception& ex)
	{
		std::cerr << "[CRITICAL ERROR] Failure reading configuration key. "
				<< ex.what() << std::endl;
		throw;
	}
}

void BasicTxtLogger::ValidateDirectory()
{
	using namespace boost::filesystem;

	try
	{
		if(!exists(m_dirPath) || !is_directory(m_dirPath))
		{
			std::cerr << "[Info] Log path doesn't exists. Creating a valid path." << std::endl;
			if(!create_directory(m_dirPath))
			{
				throw std::exception();
			}
		}
	}
	catch(const std::exception& ex)
	{
		std::cerr << "[CRITICAL ERROR] Error accessing directory: " << m_dirPath << std::endl;
		throw;
	}

}

void BasicTxtLogger::CleanLogs()
{

}

void BasicTxtLogger::CreateNewLogFile()
{
	time_t rawTime;
	std::tm* timeInfo;

	std::time(&rawTime);
	timeInfo = std::localtime(&rawTime);

	char timeBuffer[16];
	std::strftime(timeBuffer, 16, "%Y%m%d_%H%M%S", timeInfo);

	std::string path = m_dirPath
			+ ((*m_dirPath.rbegin() == '/') ? "" : "/")
			+ TEMPLATE_LOG_NAME_HEADER
			+ timeBuffer
			+ TEMPLATE_LOG_NAME_EXTENSION;

	m_log.open(path.c_str(), std::ofstream::out | std::ofstream::trunc);

	if(!m_log.is_open())
	{
		throw std::ios_base::failure("Cannot open the log file.");
	}
}

void BasicTxtLogger::WriteInfo(const std::string& msg)
{
	m_log << TEMPLATE_INFO << msg << std::endl;
}

void BasicTxtLogger::WriteWarning(const std::string& msg)
{
	m_log << TEMPLATE_WARNING << msg << std::endl;
}

void BasicTxtLogger::WriteError(const std::string& msg)
{
	m_log << TEMPLATE_ERROR << msg << std::endl;
}

BasicTxtLogger::~BasicTxtLogger()
{
	m_log.close();
}
