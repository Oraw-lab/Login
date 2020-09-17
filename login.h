#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Encryption.h"
#include "AccountObjects.h"
#include "NormalAccount.h"
using namespace std;


class Login : Encryption{
	// accountFile - all passwords and user names
	string accountFile{};
	// map for authenticate
	map <string, pair<string,accountType>> allAccount{};
	// checking if user logged in succsfully 
	bool loginPass = false;
public:
	// constructor 
	Login(string _accountFiles);
	// user log on
	int logon(const account accountTry);
	// creating account
	void createAccount(accountType account, bool firstTime);

private:
	// not implement yet
	int stringToHexa(string accountDetails);
	// loading map
	void loadAccounts();
	// getting account
	void gettingDetails(unsigned int& index, const string line, string& details, bool endOfLine);
	// getting premissions
	virtual accountType gettingAccountType(const int type);
};

