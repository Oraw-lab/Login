#include "login.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
/*
arugs = string _accountFile = file should contain username password with format of "username password premissions"
design = creating a map full of username and passowrd
return = None 
*/
Login::Login(string _accountFile) {
	accountFile = _accountFile;
	// calling loadAccount to init the map
	loadAccounts();
}
/*
arugs = None - using accountFile variable of current object .
design = loading map 
return = None
*/
void Login::loadAccounts() {
	// creating fstrean object
	fstream newFile;
	// opening current file
	newFile.open(accountFile, ios::in);
	// checking if file is open
	if (newFile.is_open()) {
		// init strings
		string line, account, password, tempPremissions;
		// creating accountType
		accountType premissions = accountType::notDef;
		// start to go over each line
		while (getline(newFile, line)) {
			// going over each char in line
			for (unsigned int i = 0; i < line.size(); i++) {
				// if line == space we done getting user name
				if (line[i] == ' ') {
					// calling getting details to get password
					gettingDetails(i, line, password);
					// calling getting details to get premissions of user
					gettingDetails(i, line, tempPremissions);
					try {
						// calling gettingAccountType to get premissions, converting from string to int since gettingAccountType expects int.
						premissions = gettingAccountType(stoi(tempPremissions));
					}catch(int){
						// catching int type from gettingAccountType = unknown premissions
						cout << "unknown account type" << endl;
					}
					// breaking to not add line[i] to account again.
					break;
				}
				// adding the char to account
				account += line[i];
			}
		// inserting to allAccount (hash map) syntax of map is string, pair(string,accountType)
		// creating a pair and inserting
		allAccount.insert({ account , make_pair(password,premissions) });
		// initalizing all variable to NULL
		account = {}, password = {}, tempPremissions = {};
		premissions = accountType::notDef;
		}

	}

}
/*
arugs = int index = getting char postion at current line , string line = getting whole line on where we stand , details = we change details accorrdinly - based on text.
design = getting password / premissions  
return = None , chaning variable by value.
*/
void Login::gettingDetails(unsigned int &index, const string line, string &details) {
	// starting to go over the line at index + 1 
	for (unsigned int j = index + 1; j < line.size(); j++) {
		// if char is space we finished getting password / premissions
		if (line[j] == ' ') {
			// index = to j to not go over the same chars
			index = j;
			// returning
			return;
		}
		// if we didnt get to if statment we add the char ti details
		details += line[j];
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
			if (exists.first == accountTry.accountPassword) {
				// User able to login , setting logpass to true
				loginPass = true;
				cout << "You were able to login";
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
arugs = accountType - to get user premissions
design = creating another user to log in
return = None, changing login file
*/
void Login::createAccount(accountType account) {
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
	cout << "What user permissons we want 1 = normal user , 0 = admin ";
	cin >> premissions;
	// formatting the string to fit for file
	string toAppend = "\n" + accountName + " " + accountPassword + " " + premissions;
	// writing to file
	ofstream outfile;
	outfile.open(accountFile, ios_base::app);
	outfile << toAppend;
	// converting to accountype and inserting to hash map
	accountType myPremssions = gettingAccountType(stoi(premissions));
	allAccount.insert({ accountName,make_pair(accountPassword,myPremssions) });

}


int Login::stringToHexa(string accountDetial)
{
	return 0;
}
