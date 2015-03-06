#include "ParametersContainer.h"
#include "ParameterPointer.h"
#include <Utils/MapUtils.h>

ParametersContainer::~ParametersContainer()
{
	ParametersPointersMap::iterator it;

	for (it = m_parameters.begin(); it != m_parameters.end(); ++it)
		delete it->second;
}

void ParametersContainer::SetParameter(const std::string& name, float value)
{
	ParameterPointer* parameterPointer = MapUtils::Find(m_parameters, name);
	if (parameterPointer == NULL)
	{
		assert(false);
		return;
	}

	parameterPointer->SetFloat(value);
}

void ParametersContainer::SetParameter(const std::string& name, const sm::Vec3& value)
{
	ParameterPointer* parameterPointer = MapUtils::Find(m_parameters, name);
	if (parameterPointer == NULL)
	{
		assert(false);
		return;
	}

	parameterPointer->SetVec3(value);
}

void ParametersContainer::SetParameter(const std::string& name, const sm::Vec4& value)
{
	ParameterPointer* parameterPointer = MapUtils::Find(m_parameters, name);
	if (parameterPointer == NULL)
	{
		assert(false);
		return;
	}

	parameterPointer->SetVec4(value);
}

void ParametersContainer::RegisterParameter(const std::string& name, float* parameter)
{
	assert(!MapUtils::HasKey(m_parameters, name));

	m_parameters[name] = new ParameterPointer(parameter);
}

void ParametersContainer::RegisterParameter(const std::string& name, sm::Vec3* parameter)
{
	assert(!MapUtils::HasKey(m_parameters, name));

	m_parameters[name] = new ParameterPointer(parameter);
}

void ParametersContainer::RegisterParameter(const std::string& name, sm::Vec4* parameter)
{
	assert(!MapUtils::HasKey(m_parameters, name));

	m_parameters[name] = new ParameterPointer(parameter);
}
