/**
 * @class DecodeBinElement
 * 
 * @brief Element used to decode compressed streams like MPEG stream
 *
 * @date Aug 28, 2014
 * @author Aleksander Bulski
 */

#ifndef DECODEBINELEMENT_H_
#define DECODEBINELEMENT_H_

#include "../StreamElement.h"

class DecodeBinElement: public StreamElement
{
public:
	DecodeBinElement(const std::string& name);

	StreamElementType GetType() const override;

	virtual ~DecodeBinElement();

protected:
	StreamElementType m_type;

	void InitializeValueTypes() override;
};

#endif /* DECODEBINELEMENT_H_ */
