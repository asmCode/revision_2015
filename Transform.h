#pragma once

#include <Math/Vec3.h>
#include <Math/Quat.h>
#include <Math/Matrix.h>

class Transform
{
public:
	Transform();

	void SetPosition(const sm::Vec3& position);
	void SetRotation(const sm::Quat& rotation);
	void SetScale(const sm::Vec3& scale);

	const sm::Vec3& GetPosition() const;
	const sm::Quat& GetRotation() const;
	const sm::Vec3& GetScale() const;

	sm::Vec3 GetForward();
	sm::Vec3 GetRight();
	sm::Vec3 GetUp();

	void SetForward(const sm::Vec3& forward);

	const sm::Matrix& GetMatrix();

private:
	bool m_isDirty;

	sm::Matrix m_matrix;

	sm::Vec3 m_position;
	sm::Quat m_rotation;
	sm::Vec3 m_scale;

	void UpdateMatrix();
};
