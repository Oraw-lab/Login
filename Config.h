#pragma once
#include <Windows.h>
#include <string>
#include <wchar.h>
using namespace std;

class Config {
public:
	// Files for program
	string malwareFileString;
	string placedFiles;
	string mySQL;
	Config();
	// getting files paths
	string createAccountFile(int type);
private:
	// formating wchar_t to string
	string formatChars(wchar_t toFormat[MAX_PATH]);
};