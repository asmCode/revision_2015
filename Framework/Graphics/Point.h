#pragma once

namespace sm
{
	template <typename T>
	class Point
	{
	public:
		Point()
		{
		}
		
		Point(T x, T y)
		{
			this ->X = x;
			this ->Y = y;
		}

		bool operator==(const Point<T>& right)
		{
			return X == right.X && Y == right.Y;
		}
		
		T X;
		T Y;
	};
}
