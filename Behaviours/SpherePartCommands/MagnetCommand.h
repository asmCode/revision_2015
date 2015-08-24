#pragma once

#include "SphereCommandBase.h"
#include <Math/Vec3.h>
#include <vector>

class Magnet;

class MagnetCommand : public SphereCommandBase
{
public:
	MagnetCommand(std::vector<Magnet*>& magnets);
	~MagnetCommand();

	bool Update();

private:
	std::vector<Magnet*>& m_magnets;

	void SetSpherePart(SpherePart* spherePart);
};
