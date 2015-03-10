#include "Matrix.h"

namespace sm
{
	Matrix Matrix::Identity = CreateIdentityMatrix();

	Matrix Matrix::CreateIdentityMatrix()
	{
		Matrix mat;
		mat.a[0] = 1.0f;
		mat.a[1] = 0.0f;
		mat.a[2] = 0.0f;
		mat.a[3] = 0.0f;
		mat.a[4] = 0.0f;
		mat.a[5] = 1.0f;
		mat.a[6] = 0.0f;
		mat.a[7] = 0.0f;
		mat.a[8] = 0.0f;
		mat.a[9] = 0.0f;
		mat.a[10] = 1.0f;
		mat.a[11] = 0.0f;
		mat.a[12] = 0.0f;
		mat.a[13] = 0.0f;
		mat.a[14] = 0.0f;
		mat.a[15] = 1.0f;

		return mat;
	}

	Matrix Matrix::CreateLookAt(const sm::Vec3 &forward, const sm::Vec3 &worldUp)
	{
		sm::Matrix lookAt;

		sm::Vec3 right = (forward * worldUp).GetNormalized();
		sm::Vec3 up = right * forward;

		lookAt.a[0] = right.x;
		lookAt.a[1] = right.y;
		lookAt.a[2] = right.z;
		lookAt.a[3] = 0.0f;

		lookAt.a[4] = up.x;
		lookAt.a[5] = up.y;
		lookAt.a[6] = up.z;
		lookAt.a[7] = 0.0f;

		lookAt.a[8] = forward.x;
		lookAt.a[9] = forward.y;
		lookAt.a[10] = forward.z;
		lookAt.a[11] = 0.0f;

		lookAt.a[12] = 0.0f;
		lookAt.a[13] = 0.0f;
		lookAt.a[14] = 0.0f;
		lookAt.a[15] = 1.0f;

		return lookAt;
	}
}
