#include "Line.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::nothrow;

Line::Line() : colour(nullptr) {}

Line::Line(const Line& newLine) : colour(nullptr)
{
	begin = newLine.begin;
	end = newLine.end;
	setColour(newLine.colour);
}

Line& Line::operator= (const Line& newLine)
{
	if (this != &newLine)
	{
		begin = newLine.begin;
		end = newLine.end;
		setColour(newLine.colour);
	}
	return *this;
}

Line::Line(int x1, int y1, int x2, int y2, char* newColour) :
begin(x1, y1), end(x2, y2), colour(nullptr)
{
	swapIfNeeded(begin);
	swapIfNeeded(end);
	setColour(newColour);
}

Line:: ~Line()
{
	delete[] colour;
}

void Line::setX1(int newX1)
{
	begin.setX(newX1);
}

void Line::setY1(int newY1)
{
	begin.setY(newY1);
}

void Line::setX2(int newX2)
{
	end.setX(newX2);
}

void Line::setY2(int newY2)
{
	end.setY(newY2);
}

void Line::setColour(char* newChar)
{
	delete[] colour;
	size_t length = strlen(newChar) + 1;
	colour = new(nothrow) char[length];
	if (!colour) throw;
	strcpy_s(colour, length, newChar);
}



void Line::arrangeLine(int i, char* fileContent, Line& line1, int& countLines)
{
	for (int j = i; fileContent[j] != '>'; ++j, ++countLines)
	{
		char* temp = nullptr;
		if (strcmp(convertWord(4, j, temp, fileContent), "x1=\"") == 0) 
		{
			char* tempX1 = nullptr;
			tempX1 = (convertAttribute(tempX1, (j + 4), fileContent));
			line1.setX1(convertNumber(tempX1));
			delete[] tempX1;
		}
		delete[] temp;
		if (strcmp(convertWord(4, j, temp, fileContent), "y1=\"") == 0)
		{
			char* tempY1 = nullptr;
			tempY1 = (convertAttribute(tempY1, (j + 4), fileContent));
			line1.setY1(convertNumber(tempY1));
			delete[] tempY1;
		}
		delete[] temp;
		if (strcmp(convertWord(4, j, temp, fileContent), "x2=\"") == 0)
		{
			char* tempX2 = nullptr;
			tempX2 = (convertAttribute(tempX2, (j + 4), fileContent));
			line1.setX2(convertNumber(tempX2));
			delete[] tempX2;
		}
		delete[] temp;
		if (strcmp(convertWord(4, j, temp, fileContent), "y2=\"") == 0)
		{
			char* tempY2 = nullptr;
			tempY2 = (convertAttribute(tempY2, (j + 4), fileContent));
			line1.setY2(convertNumber(tempY2));
			delete[] tempY2;
		}
		delete[] temp;
		if (strcmp(convertWord(8, j, temp, fileContent), "stroke=\"") == 0)
		{
			char* tempC = nullptr;
			tempC = (convertAttribute(tempC, (j + 8), fileContent));
			line1.setColour(tempC);
			delete[] tempC;
		}
		delete[] temp;
	}
}

char* Line::makeLines()
{
	char* X1 = nullptr;
	char* Y1 = nullptr;
	char* X2 = nullptr;
	char* Y2 = nullptr;

	size_t length = strlen("<line x1=\"") + strlen(convertChar(begin.getX(), X1)) +
		strlen("\" y1=\"") + strlen(convertChar(begin.getY(), Y1)) +
		strlen("\" x2=\"") + strlen(convertChar(end.getX(), X2)) +
		strlen("\" y2=\"") + strlen(convertChar(end.getX(), Y2)) +
		strlen("\" stroke=\"") + strlen(colour) + strlen("\" />/n") + 1;

	char* lineFigLine = new(nothrow) char[length + 1];
	if (!lineFigLine) throw;

	strcpy(lineFigLine, "<line x1=\"");
	strcat(lineFigLine, X1);
	strcat(lineFigLine, "\" y1=\"");
	strcat(lineFigLine, Y1);
	strcat(lineFigLine, "\" x2=\"");
	strcat(lineFigLine, X2);
	strcat(lineFigLine, "\" y2=\"");
	strcat(lineFigLine, Y2);
	strcat(lineFigLine, "\" stroke=\"");
	strcat(lineFigLine, colour);
	strcat(lineFigLine, "\" />\n");


	delete[] X1;
	delete[] Y1;
	delete[] X2;
	delete[] Y2;

	return lineFigLine;
}

int Line::selectLine()
{
	int x1, y1, x2, y2;
	char* colLine = new(nothrow) char[15];
	if (!colLine) throw;
	cin >> x1 >> y1 >> x2 >> y2 >> colLine;
	if (!cin)
	{
		cin.sync();
		cin.clear();
		cout << "Uncorrect data!" << endl;
		return -1;
	}

	begin.setX(x1);
	begin.setY(y1);
	end.setX(x2);
	end.setY(y2);
	setColour(colLine);
	delete[] colLine;
	return 1;
}

void Line::translate(const Point& newPoint)
{
	begin += newPoint;
	end += newPoint;
}

void Line::print()
{
	cout << "line " << begin.getX() << " " << begin.getY() << " ";
	cout << end.getX() << " " << end.getY() << " " << colour << endl;
}