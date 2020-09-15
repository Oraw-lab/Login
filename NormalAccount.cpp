#include "NormalAccount.h"
#include "AccountObjects.h"
#include <string>
#include <fstream>

/*
arugs = int premissions - determines if account admin or not
design - create object NormalAccount.
*/
NormalAccount::NormalAccount(int premissions){
	if (premissions) {
		// Account is admin
		isAdmin = true;
		myPressions = accountType::administrator;
	}
	else {
		// Account is not admin
		isAdmin = false;
		myPressions = accountType::normalUser;
	}

}

/*
arugs = AccountType - returning string of the premissions
design - getting string from accoutnType
return - string of user premissions
*/
string NormalAccount::accountTypeToString(accountType premissions)
{
	// switcher with premissions
	switch (premissions)
	{
	// returning administrator 
	case accountType::administrator:
		return "administrator";
	// returning normalUser for rest of the cases
	case accountType::normalUser:
	case accountType::notDef:
		return "normalUser";
	default:
		return "normalUser";
	}
}
/*
arugs = void
design = user creates a file in usersFolder 
return - None, create a file
*/
void NormalAccount::createFile() {
	// getting file name
	cout << "Please enter file name : " << endl;
	string fileName = {};
	cin >> fileName;
	// full path to file
	fileName = usersFolder + "\\" + fileName;
	// getting the text for the file
	cout << "What text do you want in ur file ? " << endl;
	string text = {};
	cin >> text;
	// checking if malware exists in text
	if (isMalwareExists(text)) {
		// returning if we found malware
		cout << "Ur text is malicious!";
		return;
	}
	// If we pass malware func we create a file with text
	// closing file
	ofstream outfile(fileName);
	outfile << accountTypeToString(myPressions)<< endl;
	outfile << text << endl;
	outfile.close();
}

void NormalAccount::createFolder()
{
}


