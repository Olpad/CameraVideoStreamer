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
	void Create();

	/**
	 * @brief Attempts to set the element into one of the GSTREAMER states.
	 * @param[in] newState State to set stream into.
	 * @return True if state changed successfuly.
	 */
	bool SetState(GstState newState);

	/**
	 * @brief Returns streams unique id
	 * @return ID of the stream.
	 */
	unsigned int GetID() const;

	virtual ~IMediaStream() {}
};

#endif /* IMEDIASTREAM_H_ */
