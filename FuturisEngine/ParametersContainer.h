#pragma once

#include "ParameterPointer.h"
#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <Utils/MapUtils.h>
#include <string>
#include <map>

class ParametersContainer
{
public:
	virtual ~ParametersContainer();

	template <typename T>
	void SetParameter(const std::string& name, const T& value)
	{
		ParameterPointer* parameterPointer = MapUtils::Find(m_parameters, name);
		if (parameterPointer == NULL)
		{
			assert(false);
			return;
		}

		parameterPointer->SetValue(value);
	}

protected:
	template <typename T>
	void RegisterParameter(const std::string& name, const T* parameter)
	{
		assert(!MapUtils::HasKey(m_parameters, name));

		m_parameters[name] = new ParameterPointer(parameter);
	}

private:
	typedef std::map<std::string, ParameterPointer*> ParametersPointersMap;

	std::map<std::string, ParameterPointer*> m_parameters;
};
