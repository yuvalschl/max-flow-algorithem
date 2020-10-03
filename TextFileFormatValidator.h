#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

class TextFileFormatValidator
{
private:
	static bool IsDigit(char Ch);
	static bool ValidateEdgeFormat(const string edgeString);
	static bool isEmptyString(const string str);

public:
	static void ValidateFormat(string textFileName);
};

