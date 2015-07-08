#pragma once

#include "Component.h"
#include <Math/Vec3.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>

class Transform : public Component
{
public:
	Transform(GameObject* gameObject);

	void SetParent(Transform* parent);
	const Transform* GetParent() const;

	void SetLocalPosition(const sm::Vec3& position);
	void SetLocalRotation(const sm::Quat& rotation);
	void SetLocalScale(const sm::Vec3& scale);

	void SetPosition(const sm::Vec3& position);
	void SetRotation(const sm::Quat& rotation);

	const sm::Vec3& GetLocalPosition() const;
	const sm::Quat& GetLocalRotation() const;
	const sm::Vec3& GetLocalScale() const;

	sm::Vec3 GetPosition() const;
	sm::Quat GetRotation() const;
	sm::Vec3 GetScale() const;

	sm::Vec3 GetForward();
	sm::Vec3 GetRight();
	sm::Vec3 GetUp();

	void SetForward(const sm::Vec3& forward);

	sm::Matrix GetLocalMatrix();
	sm::Matrix GetMatrix();

private:
	bool m_isDirty;

	Transform* m_parent;

	sm::Matrix m_localMatrix;

	sm::Vec3 m_localPosition;
	sm::Quat m_localRotation;
	sm::Vec3 m_localScale;

	void UpdateMatrix();
};
