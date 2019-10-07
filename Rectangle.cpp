#include <iostream>
#include <string.h>
#include "Rectangle.h"

using std::cout;
using std::cin;
using std::endl;
using std::nothrow;

Rectangle::Rectangle() : colour(nullptr) {}

Rectangle::Rectangle(const Rectangle& newRectangle) : colour(nullptr)
{
	beginPoint = newRectangle.beginPoint;
	area = newRectangle.area;
	setColour(newRectangle.colour);
}

Rectangle& Rectangle::operator= (const Rectangle& newRectangle)
{
	if (this != &newRectangle)
	{
		beginPoint = newRectangle.beginPoint;
		area = newRectangle.area;
		setColour(newRectangle.colour);
	}
	return *this;
}

Rectangle::Rectangle(int x, int y, int width, int height, char* newColour) : 
beginPoint(x, y), area( width, height), colour(nullptr)
{
	swapIfNeeded(beginPoint);
	swapIfNeeded(area);

	setColour(newColour);
}

Rectangle::~Rectangle()
{
	delete[] colour;
}

void Rectangle::setX(int newX)
{
	beginPoint.setX(newX);
}

void Rectangle::setY(int newY)
{
	beginPoint.setY(newY);
}

void Rectangle::setWidth(int newWidth)
{
	area.setX(newWidth);
}

void Rectangle::setHeight(int newHeight)
{
	area.setY(newHeight);
}

void Rectangle::setColour(char* newChar)
{
	delete[] colour;
	size_t length = strlen(newChar) + 1;
	colour = new(nothrow) char[length];
	if (!colour) throw;
	strcpy_s(colour, length, newChar);
}

void Rectangle::arrangeRect(int i, char* fileContent, Rectangle& rect1, int& countChars)
{
	for (int j = i; fileContent[j] != '>'; ++j, ++countChars)
	{
		char* temp = nullptr;
		if (strcmp(convertWord(3, j, temp, fileContent), "x=\"") == 0) 
		{
			char* tempX = nullptr;
			tempX = (convertAttribute(tempX, (j + 3), fileContent));
			rect1.setX(convertNumber(tempX));
			delete[] tempX;
		}
		delete[] temp;
		if (strcmp(convertWord(3, j, temp, fileContent), "y=\"") == 0)
		{
			char* tempY = nullptr;
			tempY = (convertAttribute(tempY, (j + 3), fileContent));
			rect1.setY(convertNumber(tempY));
			delete[] tempY;
		}
		delete[] temp;
		if (strcmp(convertWord(8, j, temp, fileContent), " width=\"") == 0)
		{
			char* tempW = nullptr;
			tempW = (convertAttribute(tempW, (j + 8), fileContent));
			rect1.setWidth(convertNumber(tempW));
			delete[] tempW;
		}
		delete[] temp;
		if (strcmp(convertWord(8, j, temp, fileContent), "height=\"") == 0)
		{
			char* tempH = nullptr;
			tempH = (convertAttribute(tempH, (j + 8), fileContent));
			rect1.setHeight(convertNumber(tempH));
			delete[] tempH;
		}
		delete[] temp;
		if (strcmp(convertWord(6, j, temp, fileContent), "fill=\"") == 0)
		{
			char* tempC = nullptr;
			tempC = (convertAttribute(tempC, (j + 6), fileContent));
			rect1.setColour(tempC);
			delete[] tempC;
		}
		delete[] temp;
	}
}

char* Rectangle::makeLines()
{
	char* newX = nullptr;
	char* newY = nullptr;
	char* width = nullptr;
	char* height = nullptr;

	size_t length = strlen("<rect x=\"") + strlen(convertChar(beginPoint.getX(), newX)) +
		strlen("\" y=\"") + strlen(convertChar(beginPoint.getY(), newY)) +
		strlen("\" width=\"") + strlen(convertChar(area.getX(), width)) +
		strlen("\" height=\"") + strlen(convertChar(area.getY(), height)) +
		strlen("\" fill=\"") + strlen(colour) + strlen("\" />\n") + 1;

	char* rectLine = new(nothrow) char[length + 1];
	if (!rectLine) throw;

	strcpy(rectLine, "<rect x=\"");
	strcat(rectLine, newX);
	strcat(rectLine, "\" y=\"");
	strcat(rectLine, newY);
	strcat(rectLine, "\" width=\"");
	strcat(rectLine, width);
	strcat(rectLine, "\" height=\"");
	strcat(rectLine, height);
	strcat(rectLine, "\" fill=\"");
	strcat(rectLine, colour);
	strcat(rectLine, "\" />\n");

	delete[] newX;
	delete[] newY;
	delete[] width;
	delete[] height;

	return rectLine;
}

int Rectangle::selectRect()
{
	int x, y, width , height;
	char* colRect = new(nothrow) char[15];
	if (!colRect) throw;
	cin >> x >> y >> width >> height >> colRect;
	if (!cin)
	{
		cin.sync();
		cin.clear();
		cout << "Uncorrect data!" << endl;
		return -1;
	}

	beginPoint.setX(x);
	beginPoint.setY(y);
	area.setX(width);
	area.setY(height);
	setColour(colRect);
	delete[] colRect;
	return 1;
}

void Rectangle::translate(const Point& newPoint)
{
	beginPoint += newPoint;
}

void Rectangle::print()
{
	cout << "rectangle " << beginPoint.getX() << " " << beginPoint.getY() << " ";
	cout << area.getX() << " " << area.getY() << " " << colour << endl;
}