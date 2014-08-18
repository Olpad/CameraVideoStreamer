/**
 * @class KnownConfigKeys
 * @brief Class used to hold static constants corresponding to defined keys in
 * the configuration file.
 */

#ifndef KNOWNCONFIGKEYES_H_
#define KNOWNCONFIGKEYES_H_

#include <string>

class KnownConfigKeys
{
public:
	static const std::string SETUP_SECTION;
	static const std::string PATH_TO_LOGS;
	static const std::string MAX_NUMBER_OF_LOG_FILES;
};

#endif /* KNOWNCONFIGKEYES_H_ */
