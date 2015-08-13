#pragma once

#include "CommandBase.h"

class Reset : public CommandBase
{
public:
	Reset();
	~Reset();

	bool Update();

private:
	void SetSpherePart(SpherePart* spherePart);
};
