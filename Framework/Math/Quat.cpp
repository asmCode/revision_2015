#include "Quat.h"
#include "Matrix.h"

namespace sm
{
	Quat Quat::FromAngleAxis(float angle, const sm::Vec3& axis)
	{
		Quat quat;
		quat.RotateToQuat(angle, axis);

		return quat;
	}

	/* gowno - jest wiecej przypadkow do uwzglednienia
	Quat Quat::FromOrtogonalMatrix(const sm::Matrix& matrix)
	{
		if (1 + matrix.a[0] + matrix.a[5] + matrix.a[10] < 0.0f)
		{
			int cipl = 0;
		}

		sm::Quat quat;
		quat.s = sqrtf(1 + matrix.a[0] + matrix.a[5] + matrix.a[10]) / 2.0f;
		float _4w = 4.0f * quat.s;
		quat.v.x = (matrix.a[6] - matrix.a[9]) / _4w;
		quat.v.y = (matrix.a[8] - matrix.a[2]) / _4w;
		quat.v.z = (matrix.a[1] - matrix.a[4]) / _4w;

		return quat;
	}
	*/

	Quat Quat::operator * (const Quat& q) const
	{
		Quat quat;

		quat.s = s * q.s - v.x * q.v.x - v.y * q.v.y - v.z * q.v.z;
		quat.v.x = s * q.v.x + v.x * q.s - v.y * q.v.z + v.z * q.v.y;
		quat.v.y = s * q.v.y + v.x * q.v.z + v.y * q.s - v.z * q.v.x;
		quat.v.z = s * q.v.z - v.x * q.v.y + v.y * q.v.x + v.z * q.s;

		return quat;
	}

	Quat Quat::FromToRotate(const sm::Vec3& from, const sm::Vec3& to)
	{
		sm::Vec3 axis = (from * to).GetNormalized();
		float angle = sm::Vec3::GetAngle(from, to);

		return Quat::FromAngleAxis(angle, axis);
	}

	Quat Quat::LookRotation(const sm::Vec3& direction, const sm::Vec3& up)
	{
		Quat quat = FromToRotate(sm::Vec3(0, 0, 1), direction);

		sm::Vec3 oldRight = quat.Rotate(sm::Vec3(1, 0, 0));
		sm::Vec3 newRight = (direction * up).GetNormalized();

		quat = FromToRotate(oldRight, newRight) * quat;

		return quat;
	}
}
