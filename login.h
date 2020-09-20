#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Encryption.h"
#include "AccountObjects.h"
#include "NormalAccount.h"
#include "SQLconnection.h"
using namespace std;


class Login :public Encryption , public SqlConnection{
	// accountFile - all passwords and user names
	// map for authenticate
	map <string, pair<string,accountType>> allAccount{};
	// checking if user logged in succsfully 
	bool loginPass = false;
public:
	/*
	arugs = string _accountFile = file should contain username password with format of "username password premissions"
	design = creating a map full of username and passowrd
	return = None
	*/
	Login( string _sqlDBpath) : Encryption(),SqlConnection(_sqlDBpath) {
		// calling loadAccount to init the map
		loadAccounts();
	}
	// user log on
	int logon(const account accountTry);
	// creating account
	void createAccount(accountType account, bool firstTime);

private:;
	// loading map
	void loadAccounts();
	// getting premissions
	virtual accountType gettingAccountType(const int type);
};

