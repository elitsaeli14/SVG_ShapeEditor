#ifndef __ReadFromFile_H__
#define __ReadFromFile_H__

#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"

class ReadFromFile
{
private:
	char* fileName;
	char* fileContent;
	size_t length;
	Shape** figures;
	int countFigures;
	int capacityFile;

public:
	ReadFromFile();
	ReadFromFile(const ReadFromFile&);
	ReadFromFile& operator=(const ReadFromFile&);
	~ReadFromFile();

	char* getFileName() const;
	void setFileName(char*);
	void setFileContent(char*);
	void setFigures(Shape**);

	void openFile();
	void saveFile(char*, int save);
	void close();
	void erase();
	void create();
	void translate();
	void print();

private:
	void searchFigures();
	void addFigure(Shape*);
	void resizeFigures(int add);
	void resizeFileContent(int i, int countChars, int add);
	char* makeAllLines();
	char* resizeFigureLines(char*& figureLines, size_t length2);
};

#endif //!__ReadFromFile_H__