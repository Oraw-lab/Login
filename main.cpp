#include <iostream>
#include "login.h"
#include "NormalAccount.h"
#include "Config.h"
using namespace std;



int main() {
	Config myConfig = Config();
	Login myLogin = Login(myConfig.accountFile);
	account myAccount{};
	cout << " What is the username ? ";
	cin >> myAccount.accountName;
	cout << " What is the password ? ";
	cin >> myAccount.accountPassword;
	int premissions = myLogin.logon(myAccount);
	NormalAccount userLoggedOn = NormalAccount(premissions, myConfig.malwareFileString, myConfig.placedFiles);
	bool termination = false;
	do {
		int myChoice = NULL;
		cout << "Account options" << endl;
		cout << "1.Create account " << endl;
		cout << "2.Create Folder" << endl;
		cout << "3.Create File" << endl;
		cin >> myChoice;
		switch (myChoice)
		{
		case 1:
			myLogin.createAccount(userLoggedOn.myPressions, false);
			break;
		case 2:
			userLoggedOn.createFolder();
			break;
		case 3:
			userLoggedOn.createFile();
			break;
		default:
			cout << "invalid choice" << endl;
			break;
		}
	} while (!termination);
	
}