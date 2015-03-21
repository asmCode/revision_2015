#include "Random.h"
#include <stdlib.h>
	
int Random::GetInt(int min, int max)
{
	return ((int)rand() % (max - min + 1)) + min;
}

float Random::GetFloat()
{
	return (float)rand() / (float)RAND_MAX;
}

float Random::GetFloat(float min, float max)
{
	return (GetFloat() * (max - min)) + min;
}

sm::Vec3 Random::GetUniVector()
{
	return GetVector().GetNormalized();
}

sm::Vec3 Random::GetVector()
{
	return sm::Vec3(
		GetFloat(-1, 1),
		GetFloat(-1, 1),
		GetFloat(-1, 1));
}

