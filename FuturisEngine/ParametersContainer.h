#pragma once

#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <string>
#include <map>

class ParameterPointer;

class ParametersContainer
{
public:
	virtual ~ParametersContainer();

	void SetParameter(const std::string& name, float value);
	void SetParameter(const std::string& name, const sm::Vec3& value);
	void SetParameter(const std::string& name, const sm::Vec4& value);

protected:
	void RegisterParameter(const std::string& name, float* parameter);
	void RegisterParameter(const std::string& name, sm::Vec3* parameter);
	void RegisterParameter(const std::string& name, sm::Vec4* parameter);

private:
	typedef std::map<std::string, ParameterPointer*> ParametersPointersMap;

	std::map<std::string, ParameterPointer*> m_parameters;
};
