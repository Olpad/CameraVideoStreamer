#include "StreamElement.h"

StreamElement::StreamElement(const std::string& elementTypeName, const std::string& elementName) :
	m_parentStream(nullptr), m_element(nullptr), ELEMENT_TYPE_NAME(elementTypeName)
{
	m_element = gst_element_factory_make(elementTypeName.c_str(), elementName.c_str());
	if(m_element == nullptr)
	{
		throw StreamElementNotCreatedException(elementName);
	}

	//gstreamer uses its own garbage collection mechanism
	gst_object_ref(m_element);
}

GstElement* StreamElement::GetRawElement()
{
	return m_element;
}

bool StreamElement::LinkElement(std::shared_ptr<IStreamElement> sinkElement)
{
	//element link/unlink operations depends on the common parent stream
	if(m_parentStream == nullptr || sinkElement->GetStream() != m_parentStream)
		return false;

	bool result = gst_element_link(m_element, sinkElement->GetRawElement());

	return result;
}

bool StreamElement::UnlinkElement(std::shared_ptr<IStreamElement> sinkElement)
{
	//element link/unlink operations depends on the common parent stream
	if(m_parentStream == nullptr || sinkElement->GetStream() != m_parentStream)
		return false;

	gst_element_unlink(m_element, sinkElement->GetRawElement());

	return true;
}

bool StreamElement::AddToStream(GstBin* stream)
{
	//element cannot be used in two streams
	if(m_parentStream != nullptr)
		return false;

	bool result = gst_bin_add (stream, m_element);

	if(result)
		m_parentStream = stream;

	return result;
}

bool StreamElement::RemoveFromStream()
{
	//if no parent stream - nothing to do
	if(m_parentStream == nullptr)
		return false;

	gst_bin_remove(m_parentStream, m_element);

	m_parentStream = nullptr;

	return true;
}

GstBin* StreamElement::GetStream()
{
	return m_parentStream;
}

StreamElement::~StreamElement()
{
	RemoveFromStream();

	// unref object from gstreamers garbage collection technique
	gst_object_unref(m_element);
}

bool StreamElement::LinkElementUsingParameters(std::shared_ptr<IStreamElement> sinkElement,
		const std::map<std::string, std::string>& params)
{
	//element link/unlink operations depends on the common parent stream
	//to set parameters the m_valueType map need to contain appropriate elements
	if(m_parentStream == nullptr || sinkElement->GetStream() != m_parentStream
			|| m_valueType.size() == 0)
		return false;

	//initialize value type map if its empty
	//its a pity that a template method cannod be called from a constructor
	if(m_valueType.size() == 0)
		InitializeValueTypes();

	bool areAllValidParams = true;
	GstCaps* newCaps = gst_caps_new_empty_simple(ELEMENT_TYPE_NAME.c_str());

	for(auto pair : params)
	{
		auto validParam = m_valueType.find(pair.first);
		if(validParam == m_valueType.end())
		{
			areAllValidParams = false;
			continue;
		}

		GValue* newVal;
		newVal = g_value_init(newVal, validParam->second);
		if(!gst_value_deserialize(newVal, pair.first.c_str()))
		{
			areAllValidParams = false;
			continue;
		}

		gst_caps_set_value(newCaps, pair.first.c_str(), newVal);
	}

	areAllValidParams = areAllValidParams
			&& gst_element_link_filtered(m_element, sinkElement->GetRawElement(), newCaps);

	return areAllValidParams;
}
