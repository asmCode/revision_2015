#pragma once

#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <string>

class Parameter
{
public:
	enum Type
	{
		Type_Float,
		Type_Vec3,
		Type_Vec4
	};

	Parameter();
	Parameter(const std::string& name);

	virtual ~Parameter();

	void SetFloat(float value);
	void SetVec3(sm::Vec3 value);
	void SetVec4(sm::Vec4 value);

	float GetFloat() const;
	const sm::Vec3& GetVec3() const;
	const sm::Vec4& GetVec4() const;

	std::string GetName() const;
	Type GetType() const;

private:
	std::string m_name;
	Type m_type;

	union ValueUnion
	{
		float Float;
		struct
		{
			sm::Vec3 Vec3;
			sm::Vec4 Vec4;
		};
	} Value;
	//void* m_value;
};
