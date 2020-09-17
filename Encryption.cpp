#include "Encryption.h"
#include <vector>
#include <string>

using namespace std;
/*
arugs = passowrd = plain passowrd
design = encrypting passowrd
return = encrypted password
*/
string Encryption::encrypt(string password)
{
	// initzliing and sizing vector
	vector<char> storePassword;
	storePassword.reserve(password.size());
	// encrypting password
	for (const auto chr : password) {
		storePassword.push_back(chr ^ key);
	}
	// converting vector to strign and returning value
	return vectorCharToString(storePassword);
}
/*
arugs = password - encrypted password
design = decrypted password for login
return - decrpyted password
*/
string Encryption::decryptString(const string password)
{
	// initlizing string and call stringToVector func
	string decrypted; 
	vector<char> toDecrypt = stringToVector(password);
	// resizing vector
	decrypted.reserve(toDecrypt.size());
	// decrypting passowrd
	for (const auto chr : toDecrypt) {
		decrypted.push_back(chr^ key);
	}
	// gettnig decrypted password
	return decrypted;
}

/*
arugs = vector <char> - converting current vector to string
design - returning string from chars vector
return - string of the passowrd
*/
string Encryption::vectorCharToString(const vector<char> password)
{
	// setting string from vector and returning string
	string encryptedPassword(password.begin(), password.end());
	return encryptedPassword;
}

/*
arugs = string - decrypted password
design = converting stirng to vector of char 
return = decrypted vector
*/
vector<char> Encryption::stringToVector(const string decrypted)
{
	// setting vector from string and returning string
	vector<char>myPasswordVec(decrypted.begin(), decrypted.end());
	return myPasswordVec;
}
