#pragma once

#include "../Math/Vec3.h"

class Random
{
public:
	//min - max lacznie
	static int GetInt(int min, int max);
	
	//0.0f - 1.0f lacznie
	static float GetFloat();
	
	static float GetFloat(float min, float max);

	// znormalizowany wektor w dowolnym kierunku
	static sm::Vec3 GetUniVector();

	// wektor w dowolnym kierunku mieszcz¹cy siê w szescianie (-1.0, 1.0 ...)
	static sm::Vec3 GetVector();
};
