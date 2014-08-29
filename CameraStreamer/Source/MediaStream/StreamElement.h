/**
 * @class StreamElement
 * 
 * @brief Abstract class to implement common elements of
 * 	the IStreamElement interface.
 *
 * @date Aug 25, 2014
 * @author Aleksander Bulski
 */

#ifndef STREAMELEMENT_H_
#define STREAMELEMENT_H_

#include <map>
#include "IStreamElement.h"

class StreamElement: public IStreamElement
{
public:
	StreamElement(const std::string& elementTypeName, const std::string& elementName);

	virtual GstElement* GetRawElement() override;

	virtual GstBin* GetStream() override;

	virtual bool LinkElementUsingParameters(std::shared_ptr<IStreamElement> sinkElement,
			const std::map<std::string, std::string>& params) override;

	virtual bool LinkElement(std::shared_ptr<IStreamElement> sinkElement) override;

	virtual bool UnlinkElement(std::shared_ptr<IStreamElement> sinkElement) override;

	virtual bool AddToStream(GstBin* stream) override;

	virtual bool RemoveFromStream() override;

	virtual GType ValidateParameter(const std::string& paramName) override;

	virtual ~StreamElement();

protected:
	GstBin* m_parentStream;
	GstElement* m_element;
	const std::string ELEMENT_TYPE_NAME;

	/**
	 * Stores all acceptable parameters with their respectable types.
	 */
	std::map<std::string, GType> m_valueType;

	void SetCapsValue(GstCaps* caps, GType type, const std::pair<std::string, std::string>& pair);

	/**
	 * @brief Template method to be called every time the object is constructed
	 * 	to fill in necessary types to m_valueType map.
	 */
	virtual void InitializeValueTypes() = 0;
};

#endif /* STREAMELEMENT_H_ */
