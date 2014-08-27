/**
 * @class BasicStreamManager
 * 
 * @brief Default stream manager which does the basic
 * 	management actions.
 *
 * @date Aug 27, 2014
 * @author Aleksander Bulski
 */

#ifndef BASICSTREAMMANAGER_H_
#define BASICSTREAMMANAGER_H_

#include <map>
#include "IStreamManager.h"
#include "../Context.h"
#include "./Streams/BasicMediaStream.h"

class BasicStreamManager: public IStreamManager
{
public:
	BasicStreamManager(Context *context);

	void Initialize() override;

	unsigned int GetNumberOfStreams() const override;

	bool SetStateOfStream(GstState state, const std::string& streamName) override;

	virtual ~BasicStreamManager();

protected:
	Context *m_context;
	std::map<std::string,std::shared_ptr<IMediaStream> > m_streams;
};

#endif /* BASICSTREAMMANAGER_H_ */
