/**
 * @class BasicMediaStream
 * 
 * @brief Creates a previously defined list of of IStreamElements
 * 	and organizes them into	sequences. Part of high level stream management.
 *
 * @date Aug 26, 2014
 * @author Aleksander Bulski
 */

#ifndef BASICMEDIASTREAM_H_
#define BASICMEDIASTREAM_H_

#include "IMediaStream.h"
#include "../Context.h"

class BasicMediaStream: public IMediaStream
{
public:
	BasicMediaStream(unsigned int streamID, Context* context);

	void Create();

	bool SetState(GstState newState);

	unsigned int GetID() const;

	virtual ~BasicMediaStream();

protected:
	const unsigned int m_id;
	Context* m_context;
	GstElement* m_pipeline;
	GstBin* m_stream;
	GstBus* m_bus;
};

#endif /* BASICMEDIASTREAM_H_ */
