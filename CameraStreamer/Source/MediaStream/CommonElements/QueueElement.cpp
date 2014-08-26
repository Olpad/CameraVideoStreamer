/**
 * @class QueueElement.cpp
 * 
 * @brief 
 *
 * @date Aug 26, 2014
 * @author Aleksander Bulski
 */

#include "QueueElement.h"

QueueElement::QueueElement(const std::string& name) :
	StreamElement("queue", name.c_str()), m_type(Filter)
{
}

QueueElement::~QueueElement()
{
	// TODO Auto-generated destructor stub
}

StreamElementType QueueElement::GetType() const
{
	return m_type;
}

void QueueElement::InitializeValueTypes()
{
}