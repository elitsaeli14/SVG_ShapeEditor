#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Point.h"

class Shape
{
public:
	virtual void translate(const Point& newPoint) = 0;
	virtual void print() = 0;
	virtual char* makeLines() = 0;
	virtual ~Shape() {}

	void swapIfNeeded(Point& newPoint);
	char* convertWord(int length, int j, char*&, char* fileContent);
	int convertNumber(char*);
	char* convertChar(int, char*&);
	char* convertAttribute(char*, int tempJ, char* fileContent);
	
public:
	virtual Shape* clone() = 0;

protected:
	Point point;
};

#endif //!__SHAPE_H__