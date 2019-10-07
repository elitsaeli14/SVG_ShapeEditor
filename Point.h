#ifndef __POINT_H__
#define __POINT_H__

class Point
{
private:
	int x;
	int y;

public:
	Point();
	Point(const Point&);
	Point& operator= (const Point&);
	Point(int newX, int newY);
	~Point() {}

	Point& operator+= (const Point&);

	void setX(int newX);
	void setY(int newY);
	int getX() const;
	int getY() const;

};

#endif //__POINT_H__