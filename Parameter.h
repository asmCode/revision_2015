#pragma once

#include "FuturisEngine/PropertyType.h"
#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <string>

class BaseTexture;

class Parameter
{
public:
	Parameter();
	Parameter(const std::string& name);

	virtual ~Parameter();

	void SetFloat(float value);
	void SetInt(int value);
	void SetVec3(sm::Vec3 value);
	void SetVec4(sm::Vec4 value);
	void SetString(const std::string& value);
	void SetTexture(BaseTexture* texture);

	float GetFloat() const;
	int GetInt() const;
	const sm::Vec3& GetVec3() const;
	const sm::Vec4& GetVec4() const;
	const std::string& GetString() const;
	BaseTexture* GetTexture() const;

	std::string GetName() const;
	PropertyType GetType() const;

private:
	std::string m_name;
	PropertyType m_type;

	union ValueUnion
	{
		float Float;
		int Int;
		BaseTexture* Texture;
		struct
		{
			sm::Vec3 Vec3;
			sm::Vec4 Vec4;
			std::string String;
		};
	} Value;
	//void* m_value;
};
