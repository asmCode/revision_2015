#pragma once

#include "BaseTexture.h"
#include <stdint.h>

class DepthTexture : public BaseTexture
{
public:
	DepthTexture(uint32_t width, uint32_t height);
};
