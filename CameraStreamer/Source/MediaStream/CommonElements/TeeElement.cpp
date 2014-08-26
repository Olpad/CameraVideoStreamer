#include "TeeElement.h"

TeeElement::TeeElement(const std::string& name) :
	StreamElement("tee", name.c_str()), m_type(Filter)
{
}

TeeElement::~TeeElement()
{
}

void TeeElement::InitializeValueTypes()
{
}

StreamElementType TeeElement::GetType() const
{
	return m_type;
}
