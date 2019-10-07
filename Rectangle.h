#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Shape.h"

class Rectangle: public Shape
{
private: 
	Point beginPoint;
	Point area;
	char* colour;

public:
	Rectangle();
	Rectangle(const Rectangle&);
	Rectangle& operator= (const Rectangle&);
	Rectangle(int x, int y, int width, int height, char* newColour);
	virtual ~Rectangle();

	virtual void translate(const Point& newPoint) override;
	virtual void print() override;
	virtual char* makeLines() override;
	virtual Shape* clone() override { return new Rectangle(*this); }

	void setX(int newX);
	void setY(int newY);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setColour(char*);

	void arrangeRect(int i, char* fileContent, Rectangle& rect1, int& countChars);
	int selectRect();
};

#endif //!_RECTANGLE_H__