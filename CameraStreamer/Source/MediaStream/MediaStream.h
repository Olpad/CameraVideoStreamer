/**
 * @class MediaStream
 * 
 * @brief Abstract class with most of the common IMediaStream
 * 	methods implemented in basic way.
 *
 * @date Aug 27, 2014
 * @author Aleksander Bulski
 */

#ifndef MEDIASTREAM_H_
#define MEDIASTREAM_H_

#include "IMediaStream.h"

class MediaStream: public IMediaStream
{
public:
	MediaStream(unsigned int streamID);

	virtual bool SetState(GstState newState) override;

	virtual unsigned int GetID() const override;

	virtual ~MediaStream();

protected:
	const unsigned int m_id;
	GstElement* m_pipeline;
	GstBin* m_stream;
	GstBus* m_bus;
};

#endif /* MEDIASTREAM_H_ */
