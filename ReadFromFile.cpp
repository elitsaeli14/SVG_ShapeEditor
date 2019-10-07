#include <iostream>
#include <fstream>
#include <string.h>

#include "ReadFromFile.h"
#include "Point.h"

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;
using std::bad_alloc;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::fstream;

ReadFromFile::ReadFromFile() : fileName(nullptr), fileContent(nullptr),
length(0), figures(nullptr), countFigures(0), capacityFile(0) 
{
	figures = new(nothrow)Shape*[countFigures];
	if (!figures) throw;
}

ReadFromFile::ReadFromFile(const ReadFromFile& newFile) :
length(newFile.length), countFigures(0),
capacityFile(newFile.capacityFile),
fileName(nullptr), fileContent(nullptr), figures(nullptr)
{
	setFileName(newFile.fileName);
	setFileContent(newFile.fileContent);
	setFigures(newFile.figures);
}

ReadFromFile& ReadFromFile::operator= (const ReadFromFile& newFile)
{
	if (this != &newFile)
	{
		length = newFile.length;
		capacityFile = newFile.capacityFile;
		setFileName(newFile.fileName);
		setFileContent(newFile.fileContent);
		setFigures(newFile.figures);
	}
	return *this;
}

ReadFromFile::~ReadFromFile()
{
	delete[] fileName;
	delete[] fileContent;
	for (int i = 0; i < countFigures; ++i)
	delete[] figures[i];
	delete[] figures;
} 

void ReadFromFile::setFileName(char* newName)
{
	if (newName == nullptr)
		return;

	delete[] fileName;
	size_t length1 = strlen(newName) + 1;
	fileName= new(nothrow) char[length1];
	if (!fileName) throw;
	strcpy_s(fileName, length1, newName);
}

void ReadFromFile::setFileContent(char* newName)
{
	if (newName == nullptr)
		return;

	delete[] fileContent;
	size_t length1 = strlen(newName) + 1;
	fileContent = new(nothrow) char[length1];
	if (!fileContent) throw;
	strcpy_s(fileContent, length1, newName);
}

void ReadFromFile::setFigures(Shape** newShape)
{
	if (newShape == nullptr)
		return;

	delete[] figures;
	figures = new(nothrow) Shape*[countFigures];
	if (!figures) throw;
	int tempCount = 0;
	for (int i = 0; i < countFigures; ++i)
	{
		figures[i] = newShape[i];
		++tempCount;
	}
	countFigures = tempCount;	
}

char* ReadFromFile::getFileName() const
{
	return fileName;
}

bool checkExist(char* file)
{
	ifstream in(file, ios::in);
	return in.good();
}

bool createFile(char* fileName)
{
	ofstream out(fileName, ios::out);
	return out.good();
}

void ReadFromFile::openFile()
{
	fileName = new(nothrow) char[200];
	if (!fileName) throw;
	cin >> fileName;
	for (int i = 0; i < strlen(fileName); ++i) // ако въведем директория
	{
		if (fileName[i] == '\\')
			fileName[i] = '/';
	}


	int countLines = 0;
	if (checkExist(fileName))
	{	
		ifstream in(fileName, ios::in | ios::binary );
		if (in.is_open())
		{
			cout << "Successfully opened " << fileName << endl;
			in.seekg(0, std::ios::end);
			length = in.tellg();

			fileContent = new(nothrow) char[length + 1];
			if (!fileContent) throw;

			in.seekg(0, ios::beg);
			in.read(fileContent, length);
			fileContent[length] = '\0';
			searchFigures();
			in.close();
		}
	}
	else
	{
		createFile(fileName);
		char temp[] = { "<?xml version=\"1.0\" standalone=\"no\"?>\n\
< !DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\
\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\
<svg>\n</svg>"};
		length = strlen(temp) + 1;
		fileContent = new(nothrow) char[length];
		if (!fileContent) throw;
		strcpy(fileContent, temp);
		fileContent[length - 1] = '\0';
	}
}

void ReadFromFile::saveFile(char* tempC , int save)
{
	if (countFigures != 0)
	{
		char* make = nullptr;
		for (int i = 0; i < length; ++i)
		{
			if (fileContent[i] == '<')
			{
				char* temp = nullptr;
				if (strcmp(figures[0]->convertWord(4, i, temp, fileContent), "<svg") == 0)
				{
					while (fileContent[i] != '>')
						++i;
					
					make = makeAllLines();
					int countRemoveLines = strlen(make);
					resizeFileContent(i, countRemoveLines, -1);
					strcat(fileContent, make);
					strcat(fileContent, "</svg>");
				}
				delete[] temp;
			}
		}
		delete[] make;
		if (save == 1)
		{
			ofstream out(fileName);
			out << fileContent;
			cout << "Successfully saved " << fileName << endl;
		}
		else
		{
			ofstream out(tempC);
			out << fileContent;
			cout << "Successfully saved " << tempC << endl;
		}
	}
	else
	{
		ofstream out(fileName);
		out << fileContent;
	}
}

void ReadFromFile::searchFigures()
{
	for (int i = 0; i < length; ++i)
	{
		{
			char temp1[8];
			int tempI = i;
			for (int j = 0; j < 8; ++j, ++tempI)
				temp1[j] = fileContent[tempI];
			temp1[7] = '\0';
			if (strcmp(temp1, "<circle") == 0)
			{
				Circle circle1;
				int countChars = 8;
				circle1.arrangeCircle((i + 7), fileContent, circle1, countChars);
				addFigure(&circle1);
			
				for (int s = countChars + i; fileContent[s] != '<'; ++s)
				{
					++countChars;
				}
				resizeFileContent(i, countChars, 1);
				--i;
			}
		}

		{
			char temp2[6];
			int tempI = i;
			for (int j = 0; j < 6; ++j, ++tempI)
				temp2[j] = fileContent[tempI];
			temp2[5] = '\0';
			if (strcmp(temp2, "<rect") == 0)
			{
				Rectangle rect1;
				int countChars1 = 6;
				rect1.arrangeRect((i + 5), fileContent, rect1, countChars1);
				addFigure(&rect1);
				for (int s = countChars1 + i; fileContent[s] != '<'; ++s)
				{
					++countChars1;
				}
				resizeFileContent(i, countChars1, 1);
				--i;
			}
			else if (strcmp(temp2, "<line") == 0)
			{
				Line line1;
				int countChars2 = 6;
				line1.arrangeLine((i + 5), fileContent, line1, countChars2);
				addFigure(&line1);
				for (int s = countChars2 + i; fileContent[s] != '<'; ++s)
				{
					++countChars2;
				}
				resizeFileContent(i, countChars2, 1);
				--i;
			}
		}	
	}
}

void ReadFromFile::addFigure(Shape* shape)
{
	resizeFigures(1);
	figures[countFigures - 1] = shape -> clone();
}

void ReadFromFile::resizeFigures(int add)
{
	int tempCount = countFigures;
	Shape** temp = new(nothrow)Shape*[tempCount + add];
	if (add < 0)
		--tempCount;
	for (int i = 0; i < tempCount ; i++)
		temp[i] = figures[i];
	delete[] figures;
	countFigures += add ;
	figures = temp;
}

void ReadFromFile::resizeFileContent(int i, int countChars, int add)
{
	int tempI = 0;
	size_t length1 = strlen(fileContent) - countChars*add;
	char* tempContent = new(nothrow) char[length1 + 1];
	if (!tempContent) throw;
	for (int j = 0; j < length1; ++j, ++tempI)
	{
		if (add > 0)
		if (j == i)
		{
			tempI = i + countChars; //premestvame tempI s tolkova pozicii napred 
									//kolkoto e duljinata na taga
		}
		if (add < 0 && j == (i + 2))
			break;
		tempContent[j] = fileContent[tempI];
	}
	if (add > 0)
		tempContent[length1] = '\0';
	else
		tempContent[tempI] = '\0';
	length = length1;
	delete[] fileContent;
	fileContent = tempContent;
}

char* ReadFromFile::makeAllLines()
{
	char* figureLines = nullptr;
	figureLines = figures[0]->makeLines();
	size_t lenght1 = strlen(figureLines) + 1;

	for (int i = 1; i < countFigures; ++i)
	{
		char* temp = nullptr;
		temp = figures[i]->makeLines();
		size_t lenght2 = strlen(temp);
		figureLines = resizeFigureLines(figureLines, lenght2);
		strcat(figureLines, temp);
		delete[] temp;
	}
	return figureLines;
}

char* ReadFromFile::resizeFigureLines(char*& figureLines, size_t lenght2)
{
	int count = strlen(figureLines);
	size_t lenght3 = count + lenght2 + 1;
	char* temp = new(nothrow) char[lenght3];
	if (!temp) throw;
	for (int i = 0; i < count; ++i)
	{
		temp[i] = figureLines[i];
	}
	temp[count] = '\0';
	delete[] figureLines;
	figureLines = temp;
	return figureLines;
}

void ReadFromFile::erase()
{
	int number;
	cin >> number;
	if (number < 1 || number > countFigures)
	{
		cout << "There is no figure number " << number << "!" << endl;
		return;
	}

	Shape* tempFig;
	if (number >= 0 && number < countFigures)
		for (int i = 0; i < countFigures - 1; ++i)
		{
			if (i >= (number - 1))
			{
				tempFig = figures[i + 1];
				figures[i + 1] = figures[i];
				figures[i] = tempFig;
			}
		}
	resizeFigures(-1);
}

void ReadFromFile::print()
{
	for (int i = 0; i < countFigures; ++i)
		figures[i]->print();
}

void ReadFromFile::create()
{
	char* figure = new(nothrow) char[30];
	cin >> figure;
	if (strcmp(figure, "circle") == 0)
	{
		Circle circle1;
		int valid = circle1.selectCircle();
		if (valid == 1)
		{
			addFigure(&circle1);
		}
	}
	else if (strcmp(figure, "rectangle") == 0)
	{
		Rectangle rect1;
		int valid = rect1.selectRect();
		if (valid == 1)
		{
			addFigure(&rect1);
		}
	}
	else if (strcmp(figure, "line") == 0)
	{
		Line line1;
		int valid = line1.selectLine();
		if (valid == 1)
		{
			addFigure(&line1);
		}
	}
	else cout << "Uncorrect figure!" << endl;
	delete[] figure;
}

void ReadFromFile::translate()
{
	if (countFigures != 0)
	{
		char* figure = new(nothrow) char[30];
		if (!figure) throw;

		cin.getline(figure, 30);
		size_t lenght = strlen(figure) + 1;
		int countWords = 0;
		int countChars = 0;
		Point point1;
		for (int i = 0; i < lenght; ++i)
		{
			if (figure[i] != ' ')
			{
				if (countFigures > 0)
				{
					++countWords;
					while (figure[i] != ' ')
						++countChars;
					char* tempWord = new(nothrow) char[countChars + 1];
					if (!tempWord) throw;
					if (strcmp(tempWord, "vertical="))
					{
						int countDig = 0;
						while (figure[i] != ' ')
							++countDig;
						char* tempNumber = new(nothrow) char[countDig + 1];
						if (!tempNumber) throw;
						point1.setX ( figures[0]->convertNumber(tempNumber) );
						delete[] tempWord;
					}
					else if (strcmp(tempWord, "horizontal="))
					{
						int countDig = 0;
						while (figure[i] != ' ')
							++countDig;
						char* tempNumber = new(nothrow) char[countDig + 1];
						if (!tempNumber) throw;
						point1.setY ( figures[0]->convertNumber(tempNumber) );
						delete[] tempWord;
					}
				}
			}
		}
		if (countWords > 2)
		{
			cout << "Uncorrect data!" << endl;
			return;
		}
		else figures[0]->translate(point1);
	}
}

void ReadFromFile::close()
{
	cout << "Successfully closed " << fileName << endl;
}
