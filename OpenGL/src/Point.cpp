#include "Point.h"

#include <algorithm>


Point::Point()
	: x(0), y(0), z(0)
{

}

Point::Point(float xx, float yy, float zz)
	: x(xx), y(yy), z(zz)
{

}

Point::~Point()
{

}

float Point::getDistance(const Point & other)
{
	float xx = other.x - x;
	float yy = other.y - y;
	float zz = other.z - z;
	return sqrt(xx * xx + yy * yy + zz * zz);
}

