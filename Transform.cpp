#include "Transform.h"
#include <Math/MathUtils.h>
#include "../GraphicsLog.h"

Transform::Transform() :
	m_isDirty(false),
	m_matrix(sm::Matrix::Identity),
	m_position(sm::Vec3(0, 0, 0)),
	m_rotation(1, 0, 0, 0),
	m_scale(sm::Vec3(1, 1, 1))
{
}

void Transform::SetPosition(const sm::Vec3& position)
{
	m_position = position;
	m_isDirty = true;
}

void Transform::SetRotation(const sm::Quat& rotation)
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

void Transform::SetForward(const sm::Vec3& forward)
{
	sm::Vec3 forwardProjXZ = sm::Vec3(forward.x, 0, forward.z).GetNormalized();

	GraphicsLog::AddSegment(GetPosition(), GetPosition() + forwardProjXZ * 0.5f, sm::Vec3(1, 1, 0));

	sm::Quat rotationX = sm::Quat::FromToRotate(sm::Vec3(0, 0, 1), forwardProjXZ);
	sm::Quat rotationY = sm::Quat::FromToRotate(forwardProjXZ, forward);

	SetRotation(rotationX * rotationY);
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
		sm::Matrix::Rotate(m_rotation) *
		sm::Matrix::ScaleMatrix(m_scale);

	m_isDirty = false;
}
