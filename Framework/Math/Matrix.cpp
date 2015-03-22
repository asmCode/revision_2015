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

	Matrix Matrix::PerspectiveMatrix(float fovH, float aspect, float znear, float zfar)
	{
		Matrix matrix = Identity;

		float fovV = 2.0f * atanf(tanf(fovH / 2.0f) / aspect);

		float f = 1.0f / tanf(fovV / 2.0f);
		float nearMinusFar = znear - zfar;

		matrix.a[0] = f / aspect;
		matrix.a[5] = f;
		matrix.a[10] = (zfar + znear) / nearMinusFar;
		matrix.a[11] = -1;
		matrix.a[14] = (2.0f * znear * zfar) / nearMinusFar;
		matrix.a[15] = 0.0f;

		return matrix;
	}

	Matrix Matrix::Ortho2DMatrix(float left, float right, float bottom, float top)
	{
		float _near = -100.0f;
		float _far = 100.0f;

		Matrix matrix = Identity;

		matrix.a[0] = 2.0f / (right - left);
		matrix.a[5] = 2.0f / (top - bottom);
		matrix.a[10] = -2.0f / (_far - _near);

		matrix.a[12] = -(right + left) / (right - left);
		matrix.a[13] = -(top + bottom) / (top - bottom);
		matrix.a[14] = -(_far + _near) / (_far - _near);

		return matrix;
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
