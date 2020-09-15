#include "Config.h"
#include <libloaderapi.h>
#include <Windows.h>
#include <string>
#include <wchar.h>

using namespace std;
/*
arugs - int type = assigning right file to variable
design = getting file name where exe is running
return = string of file name
*/
string Config::createAccountFile(int type) {
	// creating wchar_t that will hold MAX_PATH
	wchar_t  files[MAX_PATH];
	// init string
	string fileToChange{};
	// getting where exe is running from
	GetModuleFileName(NULL, files, MAX_PATH);
	// formating string 
	fileToChange = formatChars(files);
	// returning the right variable based on type
	switch (type)
	{
	case 0:
		// Account file
		return fileToChange += "\\Accounts.txt";
		break;
	case 1:
		// Malware file
		return fileToChange += "\\Malwares.txt";
		break;
	case 2:
		// Users space
		return fileToChange += "\\UserFolder";
		break;
	default:
		break;
	}
}

string Config::formatChars(wchar_t toFormat[MAX_PATH]){
	// converting from wchar_T to string
	wstring ws(toFormat);
	string strWs(ws.begin(), ws.end());
	// going over string from end to start
	for (int i = strWs.size() - 1; i > 0 ; i--) {
		// if we meeting "\\" we remove this file
		if (strWs.at(i) == '\\') {
			// returning formatted string
			return strWs.erase(i, strWs.size() - 1);
		}
	}
}

Config::Config() {
	// initalizing all variable object
	accountFile = createAccountFile(0);
	malwareFileString = createAccountFile(1);
	placedFiles = createAccountFile(2);
}