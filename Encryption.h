#pragma once
#include <string>
#include <vector>
using namespace std;

class Encryption {
	char key = 'Q';
public:
	string encrypt(string password);
	string decryptString(const string password);
private:
	string vectorCharToString(const vector<char> password);
	vector<char> stringToVector(const string decrypted);
};
