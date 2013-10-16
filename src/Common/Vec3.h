#ifndef COMMON_VEC3_H_
#define COMMON_VEC3_H_

#include "Common/Algorithm.h"

namespace Rainbow
{
	/// Structure for storing a three-dimensional vector.
	///
	/// Copyright 2010-13 Bifrost Entertainment. All rights reserved.
	/// \author Tommy Nguyen
	template<typename T>
	struct Vec3
	{
		T x, y, z;

		Vec3() : x(0), y(0), z(0) { }
		Vec3(const T x, const T y, const T z) : x(x), y(y), z(z) { }

		/// Returns whether the vector is zero.
		bool is_zero() const
		{
			return !this->x && !this->y && !this->z;
		}

		Vec3<T>& operator+=(const Vec3<T> &v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
			return *this;
		}

		Vec3<T>& operator-=(const Vec3<T> &v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
			return *this;
		}

		Vec3<T>& operator*=(const T &f)
		{
			this->x *= f;
			this->y *= f;
			this->z *= f;
			return *this;
		}
	};

	template<>
	inline bool Vec3<double>::is_zero() const
	{
		return equal(0.0, this->x) && equal(0.0, this->y) && equal(0.0, this->z);
	}

	template<>
	inline bool Vec3<float>::is_zero() const
	{
		return equal(0.0f, this->x) && equal(0.0f, this->y) && equal(0.0f, this->z);
	}
}

typedef Rainbow::Vec3<double> Vec3d;
typedef Rainbow::Vec3<float> Vec3f;

#endif
