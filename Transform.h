#pragma once

#include <Math/Vec3.h>
#include <Math/Vec3.h>
#include <Math/Matrix.h>

class Transform
{
public:
	Transform();

	void SetPosition(const sm::Vec3& position);
	void SetRotation(const sm::Vec4& rotation);
	void SetScale(const sm::Vec3& scale);

	const sm::Vec3& GetPosition() const;

	const sm::Matrix& GetMatrix();

private:
	bool m_isDirty;

	sm::Matrix m_matrix;

	sm::Vec3 m_position;
	sm::Vec4 m_rotation;
	sm::Vec3 m_scale;

	void UpdateMatrix();
};
