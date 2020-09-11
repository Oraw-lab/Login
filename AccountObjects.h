#pragma once
#include <string>
using namespace std;
struct account
{
	string accountName;
	string accountPassword;
};
enum class accountType
{
	administrator = 0, normalUser = 1, notDef = 3
};