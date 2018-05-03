#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string>
#include<cstdlib>

#include "Users&Accounts.h"
//#include "Users.h"
#include "Encrypt.h"
//#include "Loan.h"
using namespace std;

int main() {
	BaseUser* newUser = new Customer("fname","lname");
	newUser->setID(12345);
	cout << endl << "newUser: " << newUser->getID();

	ofstream outFile;
	outFile.open("testusers.dat",ios::binary); //ios::app for append
	if(!outFile)
	{
		cout << "outFile bad";
		return 1;
	}

	//Find end of file
	outFile.seekp(0,ios::end);
	cout << outFile.tellp();

	outFile.write(reinterpret_cast<char *> (newUser), sizeof(BaseUser));

	outFile.close();

 	cout << "\nClosed outFile";


 	/********************************************************************************************/

	BaseUser* newerUser = new Customer();

	ifstream inFile;
	inFile.open("testusers.dat",ios::binary | ios::in);
	if(!inFile)
	{
		cout << "inFile bad";
		return 1;
	}

	inFile.seekg(0,ios::beg);
	cout << "\ninFile opened successfully\n pos: " << inFile.tellg();

	while(inFile.read(reinterpret_cast<char *> (newerUser), sizeof(BaseUser))) {
		cout << "\nRead an object";
	}

	cout << endl << "newerUser: " << newerUser->getID();


	inFile.close();
}