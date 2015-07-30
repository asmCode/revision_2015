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

void Random::Shuffle(int* elements, int count)
{
	int max = count - 1;

	for (int i = 0; i < count; i++)
	{
		int r = GetInt(0, max);

		if (max != r)
		{
			elements[max] ^= elements[r];
			elements[r] ^= elements[max];
			elements[max] ^= elements[r];
		}

		max--;
	}
}

void Random::GetRandomUniqueArray(int* elements, int min, int max)
{
	int count = max - min + 1;
	for (int i = 0; i < count; i++)
		elements[i] = min + i;

	Shuffle(elements, count);
}
