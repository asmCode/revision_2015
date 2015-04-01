#include "ParametersContainer.h"
#include "ParameterPointer.h"

ParametersContainer::~ParametersContainer()
{
	ParametersPointersMap::iterator it;

	for (it = m_parameters.begin(); it != m_parameters.end(); ++it)
		delete it->second;
}
