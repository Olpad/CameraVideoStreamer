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

#include "MediaStream.h"
#include "../Context.h"

class BasicMediaStream: public MediaStream
{
public:
	BasicMediaStream(unsigned int streamID, Context* context);

	void Create();

	virtual ~BasicMediaStream();

protected:
	Context* m_context;
};

#endif /* BASICMEDIASTREAM_H_ */
