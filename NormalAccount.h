#pragma once
#include "login.h"
#include "Malwares.h"
#include <string>

class NormalAccount : public Malware{
public:
	string usersFolder = "C:\\Users\\user\\Desktop\\account\\Accounts_FIles_and_Foldeers";
	bool isAdmin = false;
	accountType myPressions;
	void createFile();
	void createFolder();
	NormalAccount(int premissions);
private:
	string accountTypeToString(accountType myPremissons);
};