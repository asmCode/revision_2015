#pragma once

#include <math.h>

#include "Vec3.h"

namespace sm
{
	class Matrix;

	class Quat
	{
	private:
	public:
		float s;
		Vec3 v;

		Quat()
		{
		}

		Quat(float val)
		{
			this->v.Set(val, val, val);
			this->s = val;
		}

		Quat(float s, float x, float y, float z)
		{
			this ->v.Set(x, y, z);
			this ->s = s;
		}

		void Set(float s, float x, float y, float z)
		{
			this ->v.Set(x, y, z);
			this ->s = s;
		}

		Quat operator + (const Quat& q) const
		{
			Quat ret;
			ret.v = this ->v + q.v;
			ret.s = this ->s + q.s;
			return ret;
		}

		Quat operator - (const Quat& q) const
		{
			Quat ret;
			ret.v = this ->v - q.v;
			ret.s = this ->s - q.s;
			return ret;
		}

		Quat operator * (const Quat& q) const;

		Quat operator * (float s)
		{
			Quat ret;
			ret.v = this ->v * s;
			ret.s = this ->s * s;
			return ret;
		}

		Quat operator / (float s)
		{
			Quat ret;
			ret.v = this->v / s;
			ret.s = this->s / s;
			return ret;
		}

		Quat operator - () const
		{
			return GetCoupleQuat();
		}

		Quat GetCoupleQuat() const
		{
			Quat ret;
			ret.v = v;
			ret.v.Reverse();
			ret.s = s;
			return ret;
		}

		void RotateToQuat(float a, float x, float y, float z)
		{
			v = sm::Vec3(x, y, z) * sinf(a/2.0f);
			s = cosf(a/2.0f);
			Normalize();
		}

		void RotateToQuat(float a, const Vec3& axis)
		{
			v = axis * sinf(a / 2.0f);
			s = cosf(a / 2.0f);
			Normalize();
		}

		void QuatToRotate(float &a, Vec3 &v)
		{
			a = acosf(this ->s) * 2.0f;

			//HMMMMMM;)
			if (a == 0) return;

			v = this ->v * (1.0f / sinf(a / 2.0f));
		}

		void Normalize()
		{
			float len = GetLength();

			if (len != 0.0f)
			{
				float proportion = 1.0f / len;
				v = v * proportion;
				s = s * proportion;
			}
		}

		float GetLength() const
		{
			return sqrtf((s * s) + Vec3::Dot(v, v));
		}

		Vec3 Rotate(Vec3 v)
		{
			Quat ret;
			Quat coup = GetCoupleQuat();

			ret.v = v;
			ret.s = 0.0f;
			ret = (*this) * ret;
			ret = ret * coup;

			return ret.v;
		}

		static float Dot(const sm::Quat& q1, const sm::Quat& q2);
		static Quat Slerp(const sm::Quat& begin, const sm::Quat& end, float time);
		static Quat FromAngleAxis(float angle, const sm::Vec3& axis);
		static Quat FromOrtogonalMatrix(const sm::Matrix& matrix);
		static Quat FromToRotate(const sm::Vec3& from, const sm::Vec3& to);
		static Quat LookRotation(const sm::Vec3& direction, const sm::Vec3& up = sm::Vec3(0, 1, 0));
	};
}
