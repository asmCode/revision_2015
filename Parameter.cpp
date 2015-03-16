#include "Parameter.h"

Parameter::Parameter()
{

}

Parameter::Parameter(const std::string& name) :
	m_name(name)
{
	/*
	switch (type)
	{
	case Parameter::Type_Float:
		m_value = new float();
		break;
	case Parameter::Type_Vec3:
		m_value = new sm::Vec3();
		break;
	case Parameter::Type_Vec4:
		m_value = new sm::Vec4();
		break;
	default:
		break;
	}
	*/
}

Parameter::~Parameter()
{
	/*
	switch (m_type)
	{
	case Parameter::Type_Float:
		delete (float*)m_value;
		break;
	case Parameter::Type_Vec3:
		delete (sm::Vec3*)m_value;
		break;
	case Parameter::Type_Vec4:
		delete (sm::Vec4*)m_value;
		break;
	default:
		break;
	}
	*/
}

void Parameter::SetFloat(float value)
{
	m_type = Parameter::Type_Float;
	Value.Float = value;
}

void Parameter::SetVec3(sm::Vec3 value)
{
	m_type = Parameter::Type_Vec3;
	Value.Vec3 = value;
}

void Parameter::SetVec4(sm::Vec4 value)
{
	m_type = Parameter::Type_Vec4;
	Value.Vec4 = value;
}

void Parameter::SetTexture(Texture* texture)
{
	m_type = Parameter::Type_Texture;
	Value.Texture = texture;
}

float Parameter::GetFloat() const
{
	assert(m_type == Parameter::Type_Float);
	return Value.Float;
}

const sm::Vec3& Parameter::GetVec3() const
{
	assert(m_type == Parameter::Type_Vec3);
	return Value.Vec3;
}

const sm::Vec4& Parameter::GetVec4() const
{
	assert(m_type == Parameter::Type_Vec4);
	return Value.Vec4;
}

Texture* Parameter::GetTexture() const
{
	assert(m_type == Parameter::Type_Texture);
	return Value.Texture;
}

Parameter::Type Parameter::GetType() const
{
	return m_type;
}

std::string Parameter::GetName() const
{
	return m_name;
}
