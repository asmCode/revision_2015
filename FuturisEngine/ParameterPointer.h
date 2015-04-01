#pragma once

#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <string>

class ParameterPointer
{
public:
	ParameterPointer(float* pointer);
	ParameterPointer(int* pointer);
	ParameterPointer(sm::Vec3* pointer);
	ParameterPointer(sm::Vec4* pointer);
	ParameterPointer(std::string* pointer);

	void SetFloat(float value);
	void SetInt(int value);
	void SetVec3(const sm::Vec3& value);
	void SetVec4(const sm::Vec4& value);
	void SetString(const std::string& value);

private:
	union PointerUnion
	{
		float* Float;
		int* Int;
		sm::Vec3* Vec3;
		sm::Vec4* Vec4;
		std::string* String;
	} Pointer;
};
