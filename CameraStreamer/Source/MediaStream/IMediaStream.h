/**
 * @interface IMediaStream
 * 
 * @brief Interface for every media stream managed in the application.
 *
 * @date Aug 26, 2014
 * @author Aleksander Bulski
 */

#ifndef IMEDIASTREAM_H_
#define IMEDIASTREAM_H_

#include "IStreamElement.h"

class IMediaStream
{
public:
	/**
	 * @brief Method to build all elements and link them together.
	 */
	virtual void Create() = 0;

	/**
	 * @brief Attempts to set the element into one of the GSTREAMER states.
	 * @param[in] newState State to set stream into.
	 * @return True if state changed successfuly.
	 */
	virtual bool SetState(GstState newState) = 0;

	/**
	 * @brief Returns streams unique id
	 * @return ID of the stream.
	 */
	virtual unsigned int GetID() const = 0;

	virtual ~IMediaStream() {}
};

#endif /* IMEDIASTREAM_H_ */
