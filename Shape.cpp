#include <iostream>
#include <string.h>

#include"Shape.h"

using std::cout;
using std::endl;
using std::nothrow;


void Shape::swapIfNeeded(Point& newPoint)
{
	if (newPoint.getX() < 0)
		newPoint.setX(-newPoint.getX());

	if (newPoint.getY() < 0)
		newPoint.setY(-newPoint.getY());
}

char* Shape::convertWord(int length, int j, char*& temp, char* fileContent)
{
	temp = new(nothrow) char[length + 1];
	if (!temp) throw;
	for (int z = 0; z < length; ++z, ++j)
	{
		temp[z] = fileContent[j];
	}
	temp[length] = '\0';
	return temp;
}

int Shape::convertNumber(char* temp)
{
	int number = 0;
	int length = strlen(temp) - 1;
	int j = 1;

	for (int i = length; i >= 0; --i)
	{
		number += ((int)temp[i] - '0') * j;
		j *= 10;
	}
	return number;
}

char* Shape::convertAttribute(char* tempCX, int tempJ, char* fileContent)
{
	tempCX = new(nothrow) char[8];
	if (!tempCX) throw;
	int z;
	for (z = 0; fileContent[tempJ] != '\"'; ++z, ++tempJ)
		tempCX[z] = fileContent[tempJ];
	tempCX[z] = '\0';

	return tempCX;
}

char* Shape::convertChar(int number, char*& strNum)
{
	int countDig = 0;
	int decimal = 1;
	int tempNum = number;
	while (tempNum)
	{
		++countDig;
		decimal *= 10;
		tempNum /= 10;
	}
	decimal /= 10;

	strNum = new(nothrow) char[countDig + 1];
	if (!strNum) throw;

	for (int i = 0; i < countDig; ++i)
	{
		int c = number / decimal;
		strNum[i] = (char)(c + 48);
		number -= c*decimal;
		decimal /= 10;
	}
	strNum[countDig] = '\0';
	//cout << strNum << endl;
	return strNum;
}