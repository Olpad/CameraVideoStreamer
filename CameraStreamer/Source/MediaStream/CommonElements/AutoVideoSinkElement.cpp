#include "AutoVideoSinkElement.h"

AutoVideoSinkElement::AutoVideoSinkElement(const std::string& name) :
	StreamElement("autovideosink", name.c_str()), m_type(Sink)
{
}

AutoVideoSinkElement::~AutoVideoSinkElement()
{
}

StreamElementType AutoVideoSinkElement::GetType() const
{
	return m_type;
}

void AutoVideoSinkElement::InitializeValueTypes()
{
	m_valueType.insert(std::pair<std::string, GType>("sync", G_TYPE_BOOLEAN));
}
