/**
 * @class QueueElement
 * 
 * @brief Basic media queue object encapsulation to match application
 * 	media stream requirements.
 *
 * @date Aug 26, 2014
 * @author Aleksander Bulski
 */

#ifndef QUEUEELEMENT_H_
#define QUEUEELEMENT_H_

#include "../StreamElement.h"

class QueueElement: public StreamElement
{
public:
	QueueElement(const std::string& name);

	StreamElementType GetType() const override;

	virtual ~QueueElement();

protected:
	StreamElementType m_type;

	void InitializeValueTypes() override;
};

#endif /* QUEUEELEMENT_H_ */
