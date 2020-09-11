#include <iostream>
#include "login.h"
#include "NormalAccount.h"
using namespace std;

int main() {
	Login myLogin = Login("C:\\Users\\user\\Desktop\\account\\test.txt");
	account myAccount{};
	cout << " What is the username ? ";
	cin >> myAccount.accountName;
	cout << " What is the password ? ";
	cin >> myAccount.accountPassword;
	NormalAccount userLoggedOn = NULL;
	if (myLogin.logon(myAccount)) 
		 userLoggedOn = NormalAccount(0);
	else 
		userLoggedOn = NormalAccount(1);
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
			myLogin.createAccount(userLoggedOn.myPressions);
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