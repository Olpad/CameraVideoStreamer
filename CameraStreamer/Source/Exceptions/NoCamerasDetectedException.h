/**
 * @class NoCamerasDetectedException
 *
 * @brief Exception to be thrown when there are no compatible
 * 	cameras detected in the system.
 *
 * @date Aug 21, 2014
 * @author Aleksander Bulski
 */

#ifndef NOCAMERASDETECTEDEXCEPTION_H_
#define NOCAMERASDETECTEDEXCEPTION_H_

#include <string>
#include <stdexcept>

class NoCamerasDetectedException : public std::runtime_error
{
public:
	NoCamerasDetectedException()
			: std::runtime_error(std::string("No cameras found in the system."))
		{	}

};

#endif /* NOCAMERASDETECTEDEXCEPTION_H_ */
