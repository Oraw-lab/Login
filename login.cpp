#include "login.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void Login::loadAccounts() {
	for (int i = 0; i < accountV.size(); i++) {
		string encryptedPass = encrypt(password.at(i));
		allAccount.insert({ accountV.at(i),make_pair(encryptedPass,gettingAccountType(premissions.at(i))) });
	}
}
/*
arugs = const int type = account type
design = switch case of type of account, returning account type based on int , throwing int if int is not equal to 1 or 0
return = accountType - administrator / normalUser
*/
accountType Login::gettingAccountType(const int type)
{
	// switching with type int
	switch (type)
	{
	case 0:
		// returning administrator if equal to 0
		return accountType::administrator;
		break;
	case 1:
		// returning normalUser if equal to 1
		return accountType::normalUser;
		break;
	default:
		// unexpected int throw expection 
		throw(type);
		break;
	}
}
/*
arugs = account - accountTry (struct hold username and password)
design = Checking if current username and password exist in hashmap
return = 0 if account administrator , 1 if account is normalAccount , EXIT_FAILURE if login failed 3 times
*/
int Login::logon(account accountTry)
{
	int maxTries = 1;
	// creating pair of string and account type
	pair<string,accountType> exists = {};
	do {
		// making sure we dont take username and password on the first try
		if (maxTries != 1) {
			// getting username 
			cout << "Please enter account name ";
			cin >> accountTry.accountName;
			// getting password
			cout << " Please enter a password ";
			cin >> accountTry.accountPassword;
		}
		// getting the value of hashmap using accountName 
		exists = allAccount[accountTry.accountName];
		// exists.first is not NULL
		if (exists.first != "") {
			// checking if the password is equal
			if (exists.first == decryptString(accountTry.accountPassword)) {
				// User able to login , setting logpass to true
				loginPass = true;
				cout << "You were able to login" << endl;
				// returning 0 if account admin
				if (exists.second == accountType::administrator) {
					return 0;
				}
				// returning 1 if account non admin
				return 1;
			}
		}
		// if exists.first we expect that there is no such key in map
		// printing wrong username
		if(exists.first == ""){
			cout << "wrong user name" << endl;
		}
		// checking if exists.first is equal to accountPassword
		// printing wrong password if not
		else if(exists.first != accountTry.accountPassword) {
			cout << "wrong password" << endl;
		}
		// adding 1 maxTries 
		maxTries++;
	} while (maxTries != 4); // prefroming while loop 4 time
	cout << "Invalid logon exiting";
	// exiting program since user failed too many times
	exit (EXIT_FAILURE);
}
/*
arugs = accountType - to get user premissions, bool firstTime - making sure there will be at least 1 administrator account
design = creating another user to log in
return = None, changing login file
*/
void Login::createAccount(accountType account, bool firstTime) {
	// if user is not administrator breaking func
	// normal user cant create user account
	if (account != accountType::administrator) {
		cout << "Creating account with non admin right isnt allowed";
		return;
	}
	// initalizing 2 strings password and username
	// getting both from console
	string accountName, accountPassword;
	cout << "Please enter account name : ";
	cin >> accountName;
	cout << "Please eneter account password : ";
	cin >> accountPassword;
	// creating premissons for user
	string premissions{};
	// first time we create a user , always will be admin
	if(firstTime){
		premissions = "0";
	}
	else {
		// letting administrator to choose user premissions
		cout << "What user permissons we want 1 = normal user , 0 = admin ";
		cin >> premissions;
	}
	// formatting the string to fit for file
	accountPassword = encrypt(accountPassword);
	string toAppend = "\n" + accountName + " " + premissions + " " + accountPassword;
	string sqlSyn("INSERT INTO ACCOUNT VALUES('" + accountName + "'," + premissions +",'"+ accountPassword + "'" + ");");
	InsertItem(sqlSyn);
	// converting to accountype and inserting to hash map
	accountType myPremssions = gettingAccountType(stoi(premissions));
	allAccount.insert({ accountName,make_pair(accountPassword,myPremssions) });

}
