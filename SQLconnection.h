#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>
using namespace std;

class SqlConnection {
	sqlite3* db;
	string sqlPath;
	int rc;
public:
	vector<string> accountV = {};
	vector<string> password = {};
	vector<int> premissions = {};
	SqlConnection(string _sqlDBpath);
	void InsertItem(string sqlTable);
	void getAccountDB();
private:
	void goingOverSturct();
	void connectDB();
	bool checkDB();
	void createAccount(bool firstTime);
};