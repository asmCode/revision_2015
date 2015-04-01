#pragma once

#include <Math/Vec3.h>
#include <Math/Vec4.h>
#include <string>

class ParameterPointer
{
public:
	template <typename T>
	ParameterPointer(const T* pointer) :
		m_pointer(pointer) {}

	template <typename T>
	void SetValue(const T& value)
	{
		*((T*)m_pointer) = value;
	}

private:
	const void* m_pointer;
};
