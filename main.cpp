#include <iostream>
#include <fstream>
#include <cmath>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "ReadFromFile.h"

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;
using std::bad_alloc;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::fstream;

void selectCommand(char* command,ReadFromFile& file1)
{
	if (strcmp(command, "save") == 0)
		file1.saveFile(file1.getFileName(), 1);
	if (strcmp(command, "saveas") == 0)
	{
		char* temp = new(nothrow) char[200];
		if (!temp) throw;
		cin >> temp;
		file1.saveFile(temp, 0);
		delete[] temp;
	}
	else if (strcmp(command, "print") == 0)
		file1.print();
	else if (strcmp(command, "create") == 0)
		file1.create();
	else if (strcmp(command, "erase") == 0)
		file1.erase();
	//else if (strcmp(command, "translate") == 0)
	//	file1.translate();
}


int main() 
{
	char* command = new(nothrow) char[10];
	if (!command) throw;

	do
	{
		while (true)
		{
			cout << "> ";
			cin >> command;
			if (strcmp(command, "exit") == 0)
			{
				delete[] command;
				return 0;
			}
			else if (strcmp(command, "open") != 0)
			{
				cin.sync();
				cin.clear();
				cout << "Uncorrect command!" << endl;
			}
			else	
				break;
		}

		ReadFromFile file1;
		file1.openFile();
		while (strcmp(command, "exit") != 0)
		{
			cout << "> ";
			cin >> command;
			if (strcmp(command, "open") == 0)
			{
				cout << "Uncorrect command!" << endl;
				cin.sync();
				cin.clear();
				break;
			}
			if (strcmp(command, "close") == 0)
			{
				file1.close();
				cin.sync();
				cin.clear();
				break;
			}
			selectCommand(command, file1);
		}
	} while (strcmp(command, "exit") != 0);

	delete[] command;
	return 0;
}