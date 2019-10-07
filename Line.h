#ifndef __LINE_H__
#define __LINE_H__

#include "Shape.h"

class Line : public Shape
{
private: 
	Point begin;
	Point end;
	char* colour;

public:
	Line();
	Line(const Line&);
	Line& operator= (const Line&);
	Line(int x1, int y1, int x2, int y2, char* newColour);
	virtual ~Line();

	virtual void translate(const Point& newPoint) override;
	virtual void print() override;
	virtual char* makeLines() override;
	virtual Shape* clone() override { return new Line(*this); }

	void setX1(int newX1);
	void setY1(int newY1);
	void setX2(int newX2);
	void setY2(int newY2);
	void setColour(char*);

	void arrangeLine(int i, char* fileContent, Line& line1, int& countLines);
	int selectLine();
};

#endif //!__LINE_H__