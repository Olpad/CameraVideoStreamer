/**
 * @class StreamNotCreatedException
 *
 * @brief Exception to be thrown when there is a problem
 * 	creating the stream.
 *
 * @date Aug 27, 2014
 * @author Aleksander Bulski
 */

#ifndef STREAMNOTCREATEDEXCEPTION_H_
#define STREAMNOTCREATEDEXCEPTION_H_

#include <string>
#include <stdexcept>

class StreamNotCreatedException : public std::runtime_error
{
public:
	StreamNotCreatedException(const std::string& streamID)
			: std::runtime_error(std::string("Failed to create stream: ") + streamID)
		{	}

};

#endif /* STREAMNOTCREATEDEXCEPTION_H_ */
