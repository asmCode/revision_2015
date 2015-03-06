#include "ParameterPointer.h"

ParameterPointer::ParameterPointer(float* pointer)
{
	Pointer.Float = pointer;
}

ParameterPointer::ParameterPointer(sm::Vec3* pointer)
{
	Pointer.Vec3 = pointer;
}

ParameterPointer::ParameterPointer(sm::Vec4* pointer)
{
	Pointer.Vec4 = pointer;
}

void ParameterPointer::SetFloat(float value)
{
	*Pointer.Float = value;
}

void ParameterPointer::SetVec3(const sm::Vec3& value)
{
	*Pointer.Vec3 = value;
}

void ParameterPointer::SetVec4(const sm::Vec4& value)
{
	*Pointer.Vec4 = value;
}
