#include "SQLconnection.h"
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
void placeItem(const string colNameS, string currentValue);

// linked list of account details to get from SQL
struct accountDetails {
	string accountName =" ";
	string password = " " ;
	int premissions = 5;
	accountDetails* nextDetails = nullptr;
};

// global variables for linked list
accountDetails* allAccounts = new accountDetails;
accountDetails* currentAccount = allAccounts;

// callback from SQL to get data
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		placeItem(azColName[i], argv[i]);
	}
	return 0;
}

/*
arugs = colName - based on colName we assign the value , currnetValue - this is the value we assign
design = switch case on colName, if currentAccount->accountName != " " && currentAccount->password != " " && currentAccount->premissions != 5 it mean we done with current node moving to next one
return = None
*/
void placeItem(const string colNameS,string currentValue) {
	if (currentAccount->accountName != " " && currentAccount->password != " " && currentAccount->premissions != 5) {
		// creating new pointer to account details
		accountDetails* newAccount = new accountDetails;
		// creating linked list
		currentAccount->nextDetails = newAccount;
		currentAccount = newAccount;
	}
	// swtich case of colName
	// assigning right value to struct variable
	if (colNameS == "ID")
		currentAccount->accountName = currentValue;
	else if (colNameS == "PERMISSIONS")
		currentAccount->premissions = stoi(currentValue);
	else if (colNameS == "PASSWORD") 
		currentAccount->password = currentValue;
}

//connecting to SQL DB using sqlite3_open
void SqlConnection::connectDB(){
	rc = sqlite3_open(sqlPath.c_str(), &db);
	if (rc) 
		return;
	else
		EXIT_FAILURE;
}
/*
arugs = Void
design - Checking if DB in right place
return = true if exists , false if doesnt exists
*/
bool SqlConnection::checkDB()
{
	struct stat info;
	// checking DB
	if (stat(sqlPath.c_str(), &info) != 0)
		return true;
	else if (info.st_mode & S_IFDIR)
		return true;
	else
		return false;
}
/*
arugs = _sqlDBpath = where db is located
design = loading account and create db if needed
consturtor
*/
SqlConnection::SqlConnection(string _sqlDBpath) {
	sqlPath = _sqlDBpath;
	string sql;
	// if we dont have DB on computer creating table 
	if (checkDB()) {
		// connecting to create db and creating table
		connectDB();
		sql = "CREATE TABLE ACCOUNT(""ID ACCOUNT PRIMARY KEY NOT NULL,""PERMISSIONS STRING NOT NULL,""PASSWORD STRING NOT NULL);";
		InsertItem(sql);
		createAccount(true);
	}
	else {
		// connecting to DB
		connectDB();
	}
	// loading account from DB
	getAccountDB();
}
/*
arugs = sqlTable - instering node/table into DB
design = catching exepction if we cant write to DB and placing Item in db
return - None
*/
void SqlConnection::InsertItem(string sqlTable) {
	char* zErrMsg;
	// inserting node/table
	rc = sqlite3_exec(db, sqlTable.c_str(), NULL, 0, &zErrMsg);
	// catching error
	if (rc != SQLITE_OK) {
		cout << "error writing to sql" << endl;
		sqlite3_free(zErrMsg);
	}
}
/*
arugs = Void
design = getting all values from linked list
return - None
*/
void SqlConnection::goingOverSturct(){
	currentAccount = allAccounts;
	vector<accountDetails*> toDelete;
	// running whille current account it not nullptr
	while (currentAccount != nullptr) {
		// getting all vectors
		accountV.push_back(currentAccount->accountName);
		password.push_back(currentAccount->password);
		premissions.push_back(currentAccount->premissions);
		toDelete.push_back(currentAccount);
		currentAccount = currentAccount->nextDetails;
	}
	// deleting all pointers to not leak memory
	for (auto& del : toDelete) {
		delete del;
	}
}

void SqlConnection::getAccountDB(){
	string query = "SELECT * FROM ACCOUNT";
	int status = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	goingOverSturct();
}

/*
arugs = accountType - to get user premissions, bool firstTime - making sure there will be at least 1 administrator account
design = creating another user to log in
return = None, changing login file
*/
void SqlConnection::createAccount(bool firstTime) {
	// if user is not administrator breaking func
	// normal user cant create user account
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
	if (firstTime) {
		premissions = "0";
	}
	// formatting the string to fit for file
	string toAppend = "\n" + accountName + " " + premissions + " " + accountPassword;
	string sqlSyn("INSERT INTO ACCOUNT VALUES('" + accountName + "'," + premissions + ",'" + accountPassword + "'" + ");");
	InsertItem(sqlSyn);
}






