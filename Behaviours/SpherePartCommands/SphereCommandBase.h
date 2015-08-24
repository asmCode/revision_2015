#pragma once

class SpherePart;
class Transform;

class SphereCommandBase
{
public:
	SphereCommandBase();
	virtual ~SphereCommandBase();

	virtual void SetSpherePart(SpherePart* spherePart);

	virtual bool Update();

protected:
	SpherePart* m_spherePart;
	Transform* m_transform;
	Transform* m_pivotTransform;
};
