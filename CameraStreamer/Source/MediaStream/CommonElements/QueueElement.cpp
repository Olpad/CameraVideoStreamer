#include "QueueElement.h"

QueueElement::QueueElement(const std::string& name) :
	StreamElement("queue", name.c_str()), m_type(Filter)
{
}

QueueElement::~QueueElement()
{
}

StreamElementType QueueElement::GetType() const
{
	return m_type;
}

void QueueElement::InitializeValueTypes()
{
}
