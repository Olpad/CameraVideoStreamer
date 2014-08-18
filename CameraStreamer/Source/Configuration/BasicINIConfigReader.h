/**
 * @class BasicINIConfigReader
 * @brief Implementation of the IConfigurationReader to handle simple INI configuration files.
 */

#ifndef BASICINICONFIGREADER_H_
#define BASICINICONFIGREADER_H_

#include "IConfigurationReader.h"
#include "KnownConfigKeys.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>

class BasicINIConfigReader : public IConfigurationReader
{
public:
	BasicINIConfigReader(); //system context

	void Initialize() override;

	int GetKeyIntValue(const std::string& sKeyName) override;

	int TryGetKeyIntValue(const std::string& sKeyName) override;

	std::string GetKeyStringValue(const std::string& sKeyName) override;

	std::string TryGetKeyStringValue(const std::string& sKeyName) override;

	virtual ~BasicINIConfigReader();

private:
	static const std::string PATH_TO_CONFIG_INI;

	boost::property_tree::ptree m_iniConfigData;
	
};

#endif /* BASICINICONFIGREADER_H_ */
