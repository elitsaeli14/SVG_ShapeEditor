#include "Circle.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::nothrow;

Circle::Circle() : radius(0), colour(nullptr) {}

Circle::Circle(const Circle& newCircle) : radius(0), colour(nullptr)
{
	center = newCircle.center;
	radius = newCircle.radius;
	setColour(newCircle.colour);
}

Circle& Circle::operator=(const Circle& newCircle)
{
	if (this != &newCircle)
	{
		center = newCircle.center;
		radius = newCircle.radius;
		setColour(newCircle.colour);
	}
	return *this;
}

Circle::Circle(int newX, int newY, int newRadius, char* newColour) : center(newX, newY), radius(0), colour(nullptr)
{
	if (newRadius < 0) throw "Incorent value of radius!";

	radius = newRadius;
	swapIfNeeded(center);
	setColour(newColour);
}

Circle::~Circle()
{
	delete[] colour;
}

void Circle::setColour(char* newChar)
{
	delete[] colour;
	size_t length= strlen(newChar) + 1;
	colour = new(nothrow) char[length];
	if (!colour) throw;
	strcpy_s(colour,length, newChar);
}

void Circle::setX(int newX)
{
	center.setX(newX);
}

void Circle::setY(int newY)
{
	center.setY(newY);
}

void Circle::setRadius(int newRadius)
{
	radius = newRadius;
}


void Circle::arrangeCircle(int i, char* fileContent, Circle& circle1, int& countChars)
{
	for (int j = i; fileContent[j] != '>'; ++j, ++countChars)
	{
		char* temp = nullptr;
		if (strcmp(convertWord(4, j, temp, fileContent), "cx=\"") == 0) 
		{
			char* tempCX = nullptr;
			tempCX = (convertAttribute(tempCX, (j + 4), fileContent));
			circle1.setX(convertNumber(tempCX));
			delete[] tempCX;
		}
		delete[] temp;
		if (strcmp(convertWord(4, j, temp, fileContent), "cy=\"") == 0)
		{
			char* tempCY = nullptr;
			tempCY = (convertAttribute(tempCY, (j + 4), fileContent));
			circle1.setY(convertNumber(tempCY));
			delete[] tempCY;
		}
		delete[] temp;
		if (strcmp(convertWord(3, j, temp, fileContent), "r=\"") == 0)
		{
			char* tempR = nullptr;
			tempR = (convertAttribute(tempR, (j + 3), fileContent));
			circle1.setRadius(convertNumber(tempR));
			delete[] tempR;
		}
		delete[] temp;
		if (strcmp(convertWord(6, j, temp, fileContent), "fill=\"") == 0)
		{
			char* tempC = nullptr;
			tempC = (convertAttribute(tempC, (j + 6), fileContent));
			circle1.setColour(tempC);
			delete[] tempC;
		}
		delete[] temp;
	}
}

char* Circle::makeLines()
{
	char* CX = nullptr;
	char* CY = nullptr;
	char* Rad = nullptr;

	size_t length = strlen("<circle cx=\"") + strlen(convertChar(center.getX(), CX)) +
		strlen("\" cy=\"") + strlen(convertChar(center.getY(), CY)) +
		strlen("\" r=\"") + strlen(convertChar(radius, Rad)) +
		strlen("\" fill=\"") + strlen(colour) + strlen("\" />\n") + 1;

	char* circleLine = new(nothrow) char[length + 1];
	if (!circleLine) throw;

	strcpy(circleLine, "<circle cx=\"");
	strcat(circleLine, CX);
	strcat(circleLine, "\" cy=\"");
	strcat(circleLine, CY);
	strcat(circleLine, "\" r=\"");
	strcat(circleLine, Rad);
	strcat(circleLine, "\" fill=\"");
	strcat(circleLine, colour);
	strcat(circleLine, "\" />\n");


	delete[] CX;
	delete[] CY;
	delete[] Rad;

	return circleLine;
}



int Circle::selectCircle()
{
	int x, y, r;
	char* colCircle = new(nothrow) char[15];
	if (!colCircle) throw;
	cin >> x >> y >> r >> colCircle;
	if (!cin)
	{
		cin.sync();
		cin.clear();
		cout << "Uncorrect data!" << endl;
		return -1;
	}

	center.setX(x);
	center.setY(y);
	radius = r;
	setColour(colCircle);
	delete[] colCircle;
	return 1;
}
void Circle::translate(const Point& newPoint)
{
	center += newPoint;
}

void Circle::print()
{
	cout << "circle " << center.getX() << " " << center.getY() << " ";
	cout << radius << " " << colour << endl;
}

