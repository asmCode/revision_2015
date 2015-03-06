#pragma once

#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <string>

class ParameterPointer
{
public:
	ParameterPointer(float* pointer);
	ParameterPointer(sm::Vec3* pointer);
	ParameterPointer(sm::Vec4* pointer);

	void SetFloat(float value);
	void SetVec3(const sm::Vec3& value);
	void SetVec4(const sm::Vec4& value);

private:
	union PointerUnion
	{
		float* Float;
		sm::Vec3* Vec3;
		sm::Vec4* Vec4;
	} Pointer;
};
