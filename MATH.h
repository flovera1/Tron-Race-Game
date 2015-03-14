#ifndef __MATH
#define __MATH

	#include <math.h>
	#define EPSILON 1.0e-8
	#define ZERO 0.0
	#define PI 3.1415926535

//upperbound or lowerbound limits of x
	template <class T> T limit(const T &x, const T &lower, const T &upper)
	{
		if (x < lower)
			return lower;
		if (x > upper)
			return upper;
		return x;
	}
//square
	template <class T> T sqr(const T &x)
	{
		return x*x;
	}
//radians to degrees
	template <class T> T RadToDeg(const T &rad)
	{
		return (rad * 180.0) / PI;
	}
//degrees to radians
	template <class T> T DegToRad(const T &deg)
	{
		return (deg * PI) / 180.0;
	}
#endif
