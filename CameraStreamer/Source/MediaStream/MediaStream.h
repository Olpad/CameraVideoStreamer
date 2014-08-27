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

#include <list>
#include "IMediaStream.h"

class MediaStream : public IMediaStream
{
public:
	MediaStream(const std::string& streamID);

	virtual bool SetState(GstState newState) override;

	virtual void Restart() override;

	virtual const std::string& GetName() const override;

	virtual ~MediaStream();

protected:
	const std::string m_name;
	GstBus* m_bus;
	GstBin* m_bin;
	GstElement* m_pipeline;

	std::list<std::shared_ptr<IStreamElement> > m_elements;

	static int ProcessBusMessageWrapper(GstBus *bus, GstMessage *message, gpointer user_data);
};

#endif /* MEDIASTREAM_H_ */
