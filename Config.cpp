#include "Config.h"
#include <libloaderapi.h>
#include <Windows.h>
#include <string>
#include <wchar.h>

using namespace std;

string Config::createAccountFile(int type) {
	wchar_t  files[MAX_PATH];
	string fileToChange{};
	switch (type)
	{
	case 0:
		GetModuleFileName(NULL, files, MAX_PATH);
		fileToChange =  formatChars(files);
		return fileToChange += "\\Accounts.txt";
		break;
	case 1:
		GetModuleFileName(NULL, files, MAX_PATH);
		fileToChange =  formatChars(files);
		return fileToChange += "\\Malwares.txt";
		break;
	case 2:
		GetModuleFileName(NULL, files, MAX_PATH);
		fileToChange = formatChars(files);
		return fileToChange += "\\UserFolder";
		break;
	default:
		break;
	}
}

string Config::formatChars(wchar_t toFormat[MAX_PATH]){
	wstring ws(toFormat);
	string strWs(ws.begin(), ws.end());
	for (int i = strWs.size() - 1; i > 0 ; i--) {
		if (strWs.at(i) == '\\') {
			return strWs.erase(i, strWs.size() - 1);
		}
	}
}

Config::Config() {
	accountFile = createAccountFile(0);
	malwareFileString = createAccountFile(1);
	placedFiles = createAccountFile(2);
}