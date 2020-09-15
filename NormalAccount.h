#pragma once
#include "login.h"
#include "Malwares.h"
#include "Config.h"
#include <string>

class NormalAccount : public Malware{
public:
	// all files and folders will be placed here
	string usersFolder = placedFiles;
	// extra action if user is admin
	bool isAdmin = false;
	accountType myPressions;
	// funcation creates file
	void createFile();
	// not implement
	void createFolder();
	// 
	NormalAccount(int premissions);
private:
	// converts accountype to string
	string accountTypeToString(accountType myPremissons);
};