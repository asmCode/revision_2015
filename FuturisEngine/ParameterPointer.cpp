#include "ParameterPointer.h"

ParameterPointer::ParameterPointer(float* pointer)
{
	Pointer.Float = pointer;
}

ParameterPointer::ParameterPointer(int* pointer)
{
	Pointer.Int = pointer;
}

ParameterPointer::ParameterPointer(sm::Vec3* pointer)
{
	Pointer.Vec3 = pointer;
}

ParameterPointer::ParameterPointer(sm::Vec4* pointer)
{
	Pointer.Vec4 = pointer;
}

ParameterPointer::ParameterPointer(std::string* pointer)
{
	Pointer.String = pointer;
}

void ParameterPointer::SetFloat(float value)
{
	*Pointer.Float = value;
}

void ParameterPointer::SetInt(int value)
{
	*Pointer.Int = value;
}

void ParameterPointer::SetVec3(const sm::Vec3& value)
{
	*Pointer.Vec3 = value;
}

void ParameterPointer::SetVec4(const sm::Vec4& value)
{
	*Pointer.Vec4 = value;
}

void ParameterPointer::SetString(const std::string& value)
{
	*Pointer.String = value;
}

