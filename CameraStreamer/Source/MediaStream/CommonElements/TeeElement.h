/**
 * @class TeeElement
 * 
 * @brief Basic tee object encapsulation to match application
 * 	media stream requirements.
 *
 * @date Aug 26, 2014
 * @author Aleksander Bulski
 */

#ifndef TEEELEMENT_H_
#define TEEELEMENT_H_

#include "../StreamElement.h"

class TeeElement: public StreamElement
{
public:
	TeeElement(const std::string& name);

	StreamElementType GetType() const override;

	virtual ~TeeElement();

protected:
	StreamElementType m_type;

	void InitializeValueTypes() override;
};

#endif /* TEEELEMENT_H_ */
