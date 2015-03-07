#include "Transform.h"

Transform::Transform() :
	m_isDirty(false),
	m_matrix(sm::Matrix::Identity),
	m_position(sm::Vec3(0, 0, 0)),
	m_rotation(sm::Vec4(0, 1, 0, 0)),
	m_scale(sm::Vec3(1, 1, 1))
{
}

void Transform::SetPosition(const sm::Vec3& position)
{
	m_position = position;
	m_isDirty = true;
}

void Transform::SetRotation(const sm::Vec4& rotation)
{
	m_rotation = rotation;
	m_isDirty = true;
}

void Transform::SetScale(const sm::Vec3& scale)
{
	m_scale = scale;
	m_isDirty = true;
}

const sm::Vec3& Transform::GetPosition() const
{
	return m_position;
}

sm::Vec3 Transform::GetForward()
{
	if (m_isDirty)
		UpdateMatrix();

	return sm::Vec3(m_matrix.a[8], m_matrix.a[9], m_matrix.a[10]);
}

sm::Vec3 Transform::GetRight()
{
	if (m_isDirty)
		UpdateMatrix();

	return sm::Vec3(m_matrix.a[0], m_matrix.a[1], m_matrix.a[2]);
}

sm::Vec3 Transform::GetUp()
{
	if (m_isDirty)
		UpdateMatrix();

	return sm::Vec3(m_matrix.a[4], m_matrix.a[5], m_matrix.a[6]);
}

const sm::Matrix& Transform::GetMatrix()
{
	if (m_isDirty)
		UpdateMatrix();

	return m_matrix;
}

void Transform::UpdateMatrix()
{
	m_matrix =
		sm::Matrix::TranslateMatrix(m_position) *
		sm::Matrix::RotateAxisMatrix(m_rotation.w, m_rotation.x, m_rotation.y, m_rotation.z) *
		sm::Matrix::ScaleMatrix(m_scale);

	m_isDirty = false;
}
