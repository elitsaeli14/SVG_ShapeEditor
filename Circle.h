#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Shape.h"

class Circle: public Shape
{
private:
	Point center;
	int radius;
	char* colour;

public:
	Circle();
	Circle(const Circle&);
	Circle& operator= (const Circle&);
	Circle(int newX, int newY , int newRadius , char* newColour);
	virtual ~Circle();

	virtual void translate(const Point& newPoint) override;
	virtual void print() override;
	virtual char* makeLines() override;
	virtual Shape* clone() override { return new Circle(*this); }

	void setX(int newX);
	void setY(int newY);
	void setRadius(int newaradius);
	void setColour(char*);

	void arrangeCircle(int i, char* fileContent, Circle& circle1, int& countChars);
	int selectCircle();
};

#endif //!__CIRCLE_H__