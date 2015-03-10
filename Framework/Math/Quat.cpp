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

	Quat Quat::FromToRotate(const sm::Vec3& from, const sm::Vec3& to)
	{
		sm::Vec3 axis = (to * from).GetNormalized();
		float angle = sm::Vec3::GetAngle(from, to);

		return Quat::FromAngleAxis(angle, axis);
	}
}
