#pragma once

#ifndef __POINT_H__
#define __POINT_H__

class Point
{
public:

	float x;
	float y;
	float z;

	Point();
	Point(float xx, float yy, float zz);
	~Point();

	float getDistance(const Point &other);

};

#endif // __POINT_H__