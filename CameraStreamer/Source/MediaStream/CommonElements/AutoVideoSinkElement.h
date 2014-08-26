/**
 * @class AutoVideoSinkElement
 * 
 * @brief Basic AutoVideoSink gstreamer block encapsulation to match application
 * 	media stream requirements.
 *
 * @date Aug 27, 2014
 * @author Aleksander Bulski
 */

#ifndef AUTOVIDEOSINKELEMENT_H_
#define AUTOVIDEOSINKELEMENT_H_

#include "../StreamElement.h"

class AutoVideoSinkElement: public StreamElement
{
public:
	AutoVideoSinkElement(const std::string& name);

	StreamElementType GetType() const override;

	virtual ~AutoVideoSinkElement();

protected:
	StreamElementType m_type;

	void InitializeValueTypes() override;
};

#endif /* AUTOVIDEOSINKELEMENT_H_ */
