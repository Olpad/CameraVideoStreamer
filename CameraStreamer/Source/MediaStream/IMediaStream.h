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
#include "../Exceptions/StreamNotCreatedException.h"

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
	 * @brief Sets stream into ready and then playing mode.
	 */
	virtual void Restart() = 0;

	/**
	 * @brief Returns streams unique name
	 * @return Name of the stream.
	 */
	virtual const std::string& GetName() const = 0;

	virtual ~IMediaStream() {}

protected:
	/**
	 * @brief Message handler for a bus associated with this stream.
	 * @param[in] bus Bus associated with this stream.
	 * @param[in] message Message to handle by the method.
	 * @param[in] user_data Pointer to this class instance.
	 */
	virtual int ProcessBusMessage(GstBus *bus, GstMessage *message, gpointer user_data) = 0;
};

#endif /* IMEDIASTREAM_H_ */
