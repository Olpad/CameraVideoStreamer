#include "DecodeBinElement.h"

DecodeBinElement::DecodeBinElement(const std::string& name) :
	StreamElement("decodebin", name.c_str()), m_type(Filter)
{
}

DecodeBinElement::~DecodeBinElement()
{
}

StreamElementType DecodeBinElement::GetType() const
{
	return m_type;
}

void DecodeBinElement::InitializeValueTypes()
{
}
