#include "NormalAccount.h"
#include "AccountObjects.h"
#include <string>
#include <fstream>
NormalAccount::NormalAccount(int premissions){
	if (premissions) {
		isAdmin = true;
		myPressions = accountType::administrator;
	}
	else {
		isAdmin = false;
		myPressions = accountType::normalUser;
	}

}

string NormalAccount::accountTypeToString(accountType premissions)
{
	switch (premissions)
	{
	case accountType::administrator:
		return "administrator";
	case accountType::normalUser:
		return "normalUser";
	case accountType::notDef:
		return "normalUser";
	default:
		return "normalUser";
	}
}

void NormalAccount::createFile() {
	cout << "Please enter file name : " << endl;
	string fileName = {};
	cin >> fileName;
	fileName = usersFolder + "\\" + fileName;
	cout << "What text do you want in ur file ? " << endl;
	string text = {};
	cin >> text;
	if (isMalwareExists(text)) {
		cout << "Ur text is malicious!";
		return;
	}
	ofstream outfile(fileName);
	outfile << accountTypeToString(myPressions)<< endl;
	outfile << text << endl;
	outfile.close();
}

void NormalAccount::createFolder()
{
}


