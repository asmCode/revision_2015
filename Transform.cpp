#include "Transform.h"
#include "FuturisEngine/PropertyContainer.h"
#include <Math/MathUtils.h>
#include "../GraphicsLog.h"

Transform::Transform(GameObject* gameObject) :
	Component("Transform", gameObject),
	m_isDirty(false),
	m_parent(NULL),
	m_localMatrix(sm::Matrix::Identity),
	m_localPosition(sm::Vec3(0, 0, 0)),
	m_localRotation(1, 0, 0, 0),
	m_localScale(sm::Vec3(1, 1, 1))
{
	GetPropertyContainer()->AddProperty<Transform, sm::Vec3>(
		"Position", PropertyType_Vec3, this, &Transform::SetPosition, &Transform::GetPosition);

	GetPropertyContainer()->AddProperty<Transform, sm::Quat>(
		"Rotation", PropertyType_Quat, this, &Transform::SetRotation, &Transform::GetRotation);

	/*GetPropertyContainer()->AddProperty<Transform, sm::Vec3>(
		"Scale", PropertyType_Vec3, this, &Transform::SetLocalScale, &Transform::GetLocalScale);*/
}

void Transform::SetParent(Transform* parent)
{
	m_parent = parent;

	if (m_parent != nullptr)
		m_parent->AddChild(this);
}

const Transform* Transform::GetParent() const
{
	return m_parent;
}

const std::vector<Transform*>& Transform::GetChildren() const
{
	return m_children;
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
	if (m_parent == NULL)
		SetLocalPosition(position);
	else
		SetLocalPosition(m_parent->GetMatrix().GetInversed() * position);
}

void Transform::SetRotation(const sm::Quat& rotation)
{
	if (m_parent == NULL)
		SetLocalRotation(rotation);
	else
		SetLocalRotation(rotation * m_parent->GetRotation().GetCoupleQuat());
}

sm::Vec3 Transform::GetPosition() const
{
	if (m_parent == NULL)
		return m_localPosition;

	return m_parent->GetMatrix() * m_localPosition;
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
	SetRotation(sm::Quat::LookRotation(forward));
}

sm::Matrix Transform::GetLocalMatrix()
{
	if (m_isDirty)
		UpdateMatrix();

	return m_localMatrix;
}

sm::Matrix Transform::GetMatrix()
{
	if (m_parent == NULL)
		return GetLocalMatrix();

	return m_parent->GetMatrix() * GetLocalMatrix();
}

void Transform::UpdateMatrix()
{
	m_localMatrix =
		sm::Matrix::TranslateMatrix(m_localPosition) *
		sm::Matrix::Rotate(m_localRotation) *
		sm::Matrix::ScaleMatrix(m_localScale);

	m_isDirty = false;
}

void Transform::AddChild(Transform* transform)
{
	assert(transform != NULL);

	m_children.push_back(transform);
}
