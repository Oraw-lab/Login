#pragma once
#include "login.h"
#include "Malwares.h"
#include "Config.h"
#include <string>
#include <Windows.h>
#include<direct.h>

class NormalAccount : public Malware{
public:
	// all files and folders will be placed here
	string usersFolder;
	// extra action if user is admin
	accountType myPressions;
	// funcation creates file
	void createFile();
	// not implement
	void createFolder();
	/*
	arugs = int premissions - determines if account admin or not
	design - create object NormalAccount.
	*/
	NormalAccount(int premissions, string _malwarePath, string _usersFolder) : Malware(_malwarePath){
		usersFolder = _usersFolder;
		if (checkDir()) {
			if (_mkdir(_usersFolder.c_str()) == -1) {
				cout << "Error creating Dir" << endl;
				exit(EXIT_FAILURE);
			}
		}
		if (premissions == 0) 
			// Account is admin1
			myPressions = accountType::administrator;
		else
			// Account is not admin
			myPressions = accountType::normalUser;
	}
private:
	// converts accountype to string
	string accountTypeToString(accountType myPremissons);
	// checks if userFolder exists in OS
	int checkDir();
};