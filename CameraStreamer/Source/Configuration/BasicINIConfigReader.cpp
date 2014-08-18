#include "BasicINIConfigReader.h"

BasicINIConfigReader::BasicINIConfigReader()
{

}

BasicINIConfigReader::~BasicINIConfigReader()
{

}

void BasicINIConfigReader::Initialize()
{
	try
	{
		boost::property_tree::ini_parser::read_ini(PATH_TO_CONFIG_INI, m_iniConfigData);
	}
	catch (boost::property_tree::ini_parser::ini_parser_error& ex)
	{
		std::cerr << "[CRITICAL ERROR] Failure parsing configuration file: " << ex.filename()
				<< " at line: " << ex.line() << std::endl;
		throw;
	}
	catch (boost::property_tree::ptree_bad_path& ex)
	{
		std::cerr << "[CRITICAL ERROR] Failure reading configuration file: "
				<< " from path: " << PATH_TO_CONFIG_INI << std::endl;
		throw;
	}
}

int BasicINIConfigReader::GetKeyIntValue(const std::string& sKeyName)
{
	return m_iniConfigData.get<int>(sKeyName);
}

int BasicINIConfigReader::TryGetKeyIntValue(const std::string& sKeyName)
{
	try
	{
		return GetKeyIntValue(sKeyName);
	}
	catch (...)
	{
		return -1;
	}
}

std::string BasicINIConfigReader::GetKeyStringValue(const std::string& sKeyName)
{
	return m_iniConfigData.get<std::string>(sKeyName);
}

std::string BasicINIConfigReader::TryGetKeyStringValue(const std::string& sKeyName)
{
	try
	{
		return GetKeyStringValue(sKeyName);
	}
	catch (...)
	{
		return "";
	}
}

std::string const BasicINIConfigReader::PATH_TO_CONFIG_INI = "./config.ini";
