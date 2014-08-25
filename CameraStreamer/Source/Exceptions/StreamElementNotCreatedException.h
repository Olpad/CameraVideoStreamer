/**
 * @class StreamElementNotCreatedException
 *
 * @brief Exception to be thrown when there is a problem
 * 	creating element of the stream.
 *
 * @date Aug 25, 2014
 * @author Aleksander Bulski
 */

#ifndef STREAMELEMENTNOTCREATEDEXCEPTION_H_
#define STREAMELEMENTNOTCREATEDEXCEPTION_H_

#include <string>
#include <stdexcept>

class StreamElementNotCreatedException : public std::runtime_error
{
public:
	StreamElementNotCreatedException(const std::string& elementName)
			: std::runtime_error(std::string("Failed to create stream element: ") + elementName)
		{	}

};

#endif /* STREAMELEMENTNOTCREATEDEXCEPTION_H_ */
