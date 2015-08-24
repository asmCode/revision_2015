#pragma once

#include "SphereCommandBase.h"

class Reset : public SphereCommandBase
{
public:
	Reset();
	~Reset();

	bool Update();

private:
	void SetSpherePart(SpherePart* spherePart);
};
