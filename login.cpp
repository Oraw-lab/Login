#include "login.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
Login::Login(string _accountFile) {
	accountFile = _accountFile;
	loadAccounts(accountFile);
}
void Login::loadAccounts(string pathFile) {
	fstream newFile;
	newFile.open(pathFile, ios::in);
	if (newFile.is_open()) {
		string line, account, password, tempPremissions;
		accountType premissions{};
		while (getline(newFile, line)) {
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ' ') {
					gettingDetails(i, line, password);
					gettingDetails(i, line, tempPremissions);
					try {
						premissions = gettingAccountType(stoi(tempPremissions));
					}catch(int type){
						cout << "unknown account type" << endl;
					}
					break;
				}
				account += line[i];
			}
		allAccount.insert({ account , make_pair(password,premissions) });
		account = {}, password = {}, tempPremissions = {};
		premissions = accountType::notDef;
		}

	}

}

void Login::gettingDetails(int &index, const string line, string &details) {
	for (int j = index + 1; j < line.size(); j++) {
		if (line[j] == ' ') {
			index = j;
			return;
		}
		details += line[j];
	}

}
accountType Login::gettingAccountType(const int type)
{
	switch (type)
	{
	case 0:
		return accountType::administrator;
		break;
	case 1:
		return accountType::normalUser;
		break;
	case 3:
		throw(type);
		break;
	default:
		throw(type);
		break;
	}
}
int Login::logon(account accountTry)
{
	pair<string,accountType> exists = {};
	do {
		if (maxTries != 1) {
			cout << "Please enter account name ";
			cin >> accountTry.accountName;
			cout << " Please enter a password ";
			cin >> accountTry.accountPassword;
		}
		exists = allAccount[accountTry.accountName];
		if (exists.first != "") {
			if (exists.first == accountTry.accountPassword) {
				loginPass = true;
				cout << "You were able to login";
				if (exists.second == accountType::administrator) {
					return 0;
				}
				return 1;
			}
		}
		if(exists.first == ""){
			cout << "wrong user name" << endl;
		}
		else {
			cout << "wrong password" << endl;
		}
		maxTries++;
	} while (maxTries != 4);
	cout << "Invalid logon exiting";
	exit (EXIT_FAILURE);
}
void Login::createAccount(accountType account) {
	if (account != accountType::administrator) {
		cout << "Creating account with non admin right isnt allowed";
		return;
	}
	string accountName, accountPassword;
	cout << "Please enter account name : ";
	cin >> accountName;
	cout << "Please eneter account password : ";
	cin >> accountPassword;
	string premissions = "1";
	string toAppend = "\n" + accountName + " " + accountPassword + " " + premissions;
	ofstream outfile;
	outfile.open(accountFile, ios_base::app);
	outfile << toAppend;
	accountType myPremssions = gettingAccountType(stoi(premissions));
	allAccount.insert({ accountName,make_pair(accountPassword,myPremssions) });

}


int Login::stringToHexa(string accountDetial)
{
	return 0;
}
