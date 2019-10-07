#include <iostream>
#include "Point.h"
 
Point::Point() : x(0), y(0) {}

Point::Point(const Point& newPoint) : x(0), y(0) 
{
	setX(newPoint.x);
	setY(newPoint.y);
}

Point& Point::operator= (const Point& newPoint)
{
	if (this != &newPoint)
	{
		setX(newPoint.x);
		setY(newPoint.y);
	}
	return *this;
}

Point::Point(int newX, int newY) : x(0), y(0)
{
	setX(newX);
	setY(newY);
}

void Point::setX(int newX)
{
	if (newX < 0)
		x = -newX;
	else
		x = newX;
}

void Point::setY(int newY)
{
	if (newY < 0)
		y = -newY;
	else
		y = newY;
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

Point& Point::operator+= (const Point& newPoint)
{
	x += newPoint.x;
	y += newPoint.y;

	return *this;
}

