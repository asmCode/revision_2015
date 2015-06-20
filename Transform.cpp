#include "Transform.h"
#include <Math/MathUtils.h>
#include "../GraphicsLog.h"

Transform::Transform() :
	m_isDirty(false),
	m_parent(NULL),
	m_localMatrix(sm::Matrix::Identity),
	m_localPosition(sm::Vec3(0, 0, 0)),
	m_localRotation(1, 0, 0, 0),
	m_localScale(sm::Vec3(1, 1, 1))
{
}

void Transform::SetLocalPosition(const sm::Vec3& position)
{
	m_localPosition = position;
	m_isDirty = true;
}

void Transform::SetLocalRotation(const sm::Quat& rotation)
{
	m_localRotation = rotation;
	m_isDirty = true;
}

void Transform::SetLocalScale(const sm::Vec3& scale)
{
	m_localScale = scale;
	m_isDirty = true;
}

void Transform::SetPosition(const sm::Vec3& position)
{
}

void Transform::SetRotation(const sm::Quat& rotation)
{
}

void Transform::SetScale(const sm::Vec3& scale)
{
}

sm::Vec3 Transform::GetPosition() const
{
	if (m_parent == NULL)
		return m_localPosition;

	return m_parent->GetPosition() + m_localPosition;
}

sm::Quat Transform::GetRotation() const
{
	if (m_parent == NULL)
		return m_localRotation;

	return m_localRotation * m_parent->GetRotation();
}

sm::Vec3 Transform::GetScale() const
{
	if (m_parent == NULL)
		return m_localScale;

	return m_parent->GetScale() * m_localScale;
}

const sm::Vec3& Transform::GetLocalPosition() const
{
	return m_localPosition;
}

const sm::Quat& Transform::GetLocalRotation() const
{
	return m_localRotation;
}

const sm::Vec3& Transform::GetLocalScale() const
{
	return m_localScale;
}

sm::Vec3 Transform::GetForward()
{
	sm::Matrix matrix = GetMatrix();

	return sm::Vec3(matrix.a[8], matrix.a[9], matrix.a[10]);
}

sm::Vec3 Transform::GetRight()
{
	sm::Matrix matrix = GetMatrix();

	return sm::Vec3(matrix.a[0], matrix.a[1], matrix.a[2]);
}

sm::Vec3 Transform::GetUp()
{
	sm::Matrix matrix = GetMatrix();

	return sm::Vec3(matrix.a[4], matrix.a[5], matrix.a[6]);
}

void Transform::SetForward(const sm::Vec3& forward)
{
	// TODO:
	//SetRotation(sm::Quat::LookRotation(forward));
}

const sm::Matrix& Transform::GetLocalMatrix()
{
	if (m_isDirty)
		UpdateMatrix();

	return m_localMatrix;
}

sm::Matrix Transform::GetMatrix()
{
	if (m_parent == NULL)
		return GetLocalMatrix();

	return GetLocalMatrix() * m_parent->GetMatrix();
}

void Transform::UpdateMatrix()
{
	m_localMatrix =
		sm::Matrix::TranslateMatrix(m_localPosition) *
		sm::Matrix::Rotate(m_localRotation) *
		sm::Matrix::ScaleMatrix(m_localScale);

	m_isDirty = false;
}
