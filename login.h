#pragma once
#include <string>
#include <iostream>
#include <map>
#include "AccountObjects.h"
#include "NormalAccount.h"
using namespace std;
class Login{
	string accountFile{};
	map <string, pair<string,accountType>> allAccount{};
	bool loginPass = false;
	int maxTries = 1;
public:
	Login(string _accountFiles);
	int logon(const account accountTry);
	void createAccount(accountType account);

private:
	int stringToHexa(string accountDetial);
	void loadAccounts(string pathFile);
	void gettingDetails(int& index, const string line, string& details);
	virtual accountType gettingAccountType(const int type);
};

