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
	case PropertyType_Float:
		m_value = new float();
		break;
	case PropertyType_Vec3:
		m_value = new sm::Vec3();
		break;
	case PropertyType_Vec4:
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
	case PropertyType_Float:
		delete (float*)m_value;
		break;
	case PropertyType_Vec3:
		delete (sm::Vec3*)m_value;
		break;
	case PropertyType_Vec4:
		delete (sm::Vec4*)m_value;
		break;
	default:
		break;
	}
	*/
}

void Parameter::SetFloat(float value)
{
	m_type = PropertyType_Float;
	Value.Float = value;
}

void Parameter::SetInt(int value)
{
	m_type = PropertyType_Int;
	Value.Int = value;
}

void Parameter::SetVec2(sm::Vec2 value)
{
	m_type = PropertyType_Vec2;
	Value.Vec2 = value;
}

void Parameter::SetVec3(sm::Vec3 value)
{
	m_type = PropertyType_Vec3;
	Value.Vec3 = value;
}

void Parameter::SetVec4(sm::Vec4 value)
{
	m_type = PropertyType_Vec4;
	Value.Vec4 = value;
}

void Parameter::SetString(const std::string& value)
{
	m_type = PropertyType_String;
	Value.String = value;
}

void Parameter::SetTexture(BaseTexture* texture)
{
	m_type = PropertyType_Texture;
	Value.Texture = texture;
}

float Parameter::GetFloat() const
{
	assert(m_type == PropertyType_Float);
	return Value.Float;
}

int Parameter::GetInt() const
{
	assert(m_type == PropertyType_Int);
	return Value.Int;
}

const sm::Vec2& Parameter::GetVec2() const
{
	assert(m_type == PropertyType_Vec2);
	return Value.Vec2;
}

const sm::Vec3& Parameter::GetVec3() const
{
	assert(m_type == PropertyType_Vec3);
	return Value.Vec3;
}

const sm::Vec4& Parameter::GetVec4() const
{
	assert(m_type == PropertyType_Vec4);
	return Value.Vec4;
}

const std::string& Parameter::GetString() const
{
	assert(m_type == PropertyType_String);
	return Value.String;
}

BaseTexture* Parameter::GetTexture() const
{
	assert(m_type == PropertyType_Texture);
	return Value.Texture;
}

PropertyType Parameter::GetType() const
{
	return m_type;
}

std::string Parameter::GetName() const
{
	return m_name;
}
