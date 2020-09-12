#pragma once
#include <string>
using namespace std;


struct account
// structs holds username and password
{
	string accountName;
	string accountPassword;
};
enum class accountType
// enum for user premissions
{
	administrator = 0, normalUser = 1, notDef = 3
};