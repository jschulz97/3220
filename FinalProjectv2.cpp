//============================================================================
// Name        : FinalProjectv1.cpp
// Author      : Andrew
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string>
#include<conio.h> //For hiding password with getch()

#include "Users&Accounts.h"
#include "Encrypt.h"
//#include "Loan.h"
using namespace std;

/**************************************************************************************************/


/****************************************************************************************************/

string enter_password();
void create_user_account();
void delete_account(int);
void deposit_withdraw(int, int);
void display_account(int);
void display_all();
void edit_account(int);
void write_account();

int main()
{
	cout << endl << "\t!!!Welcome to S&K Bank!!!";
	BaseUser* User = new Customer();

	//Log in loop
	do {
		try {
			cout << endl << "Enter your user ID or 'N' to create a new account: ";
			string id;
			cin >> id;
			if(id == "N" || id == "n") {
				create_user_account();
			}

			//Check if id is fully a number
			int idnum;
			for(auto i : id) {
				if(!isdigit(i)) 
					throw error("Invalid user ID");
			}

			//Convert id string to int
			idnum = atoi(id);

			string password = enter_password();

			User = sign_in(idnum,password);
		} catch(error e) {
			e.display();
		}

	} while(User->getID() == 1); //default value for new BaseUser


	if(User->getID() != 1) {
		char choice;
		int num;
		do {
			if(User->get_permissions() == 2) { //Menu for Bank Manager
				system("cls");
				cout << endl << "\tWelcome back " << User->getFName();
				cout << endl << endl << "0) Exit";
				cout << endl << endl << "1) New Account";




				cout << endl << endl << "1) New Account";
				cout << endl << endl << "2) Deposit";
				cout << endl << endl << "3) Withdraw";
				cout << endl << endl << "4) Balance";
				cout << endl << endl << "5) Display All Accounts";
				cout << endl << endl << "6) Close an Account";
				cout << endl << endl << "7) Edit the Details of an Account";
				cout << endl << endl << "8) Exit";
				cout << endl << endl << "Make Your Choice (1-8) and don't be a smartass and pick something besides these";
				cin >> choice;
				system("cls");
				switch(choice)
				{
				case '1':
					write_account();
					break;
				case '2':
					cout << endl << endl << "Enter Account Number: ";
					cin >> num;
					deposit_withdraw(num, 1);
					break;
				case '3':
					cout << endl << endl << "Enter Account Number: ";
					cin >> num;
					deposit_withdraw(num, 2);
					break;
				case '4':
					cout << endl << endl << "Enter Account Number: ";
					cin>>num;
					display_account(num);
					break;
				case '5':
					display_all();
					break;
				case '6':
					cout << endl << endl << "Enter Account Number: ";
					cin>>num;
					delete_account(num);
					break;
				 case '7':
					cout << endl << endl << "Enter Account Number: ";
					cin>>num;
					edit_account(num);
					break;
				 case '8':
					cout << endl << endl << "Thanks Homie";
					break;
				 default:
					 cout << "\a";
				}
				cin.ignore();
				cin.get();

			} else { //Menu for regular customers

				system("cls");
				cout << endl << "\t!!!Welcome " << User->getFName();
				cout << endl << endl << "0) Exit";
				cout << endl << endl << "1) New Account";




				cout << endl << endl << "1) New Account";
				cout << endl << endl << "2) Deposit";
				cout << endl << endl << "3) Withdraw";
				cout << endl << endl << "4) Balance";
				cout << endl << endl << "5) Display All Accounts";
				cout << endl << endl << "6) Close an Account";
				cout << endl << endl << "7) Edit the Details of an Account";
				cout << endl << endl << "8) Exit";
				cout << endl << endl << "Make Your Choice (1-8) and don't be a smartass and pick something besides these";
				cin >> choice;
				system("cls");
				switch(choice)
				{
				case '1':
					write_account();
					break;
				case '2':
					cout << endl << endl << "Enter Account Number: ";
					cin >> num;
					deposit_withdraw(num, 1);
					break;
				case '3':
					cout << endl << endl << "Enter Account Number: ";
					cin >> num;
					deposit_withdraw(num, 2);
					break;
				case '4':
					cout << endl << endl << "Enter Account Number: ";
					cin>>num;
					display_account(num);
					break;
				case '5':
					display_all();
					break;
				case '6':
					cout << endl << endl << "Enter Account Number: ";
					cin>>num;
					delete_account(num);
					break;
				 case '7':
					cout << endl << endl << "Enter Account Number: ";
					cin>>num;
					edit_account(num);
					break;
				 case '8':
					cout << endl << endl << "Thanks Homie";
					break;
				 default:
					 cout << "\a";
				}
				cin.ignore();
				cin.get();
			}

		}
		while(choice != '0');
	}
	return 0;
}



/**
 * 
 */
BaseUser* sign_in(int usrID, string encrypted_pass) {
	instream userFile;
	instream loginFile;
	userFile.open("users.dat",ios::binary);
	loginFile.open("logins.dat",ios::binary);
	if(!loginFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened. Press any key to continue.";
		return new Customer();
	}
	if(!userFile)
	{
		cout << "Something went wrong, users.dat couldn't be opened. Press any key to continue.";
		return new Customer();
	}

	Login log;
	bool found = false;
	while(loginFile.read(reinterpret_cast<char *> (&log), sizeof(Login))) {
		if(log.getID() == usrID) {
			found = true;
			if(encrypted_pass != log.getPass()) {
				cerr << "\nPassword is incorrect\n";
				return new Customer();
			}
		}
	}

	if(!found) {
		cout << "\nUser does not exist. Press any key to continue.";
		return new Customer();
	}

	BaseUser* bu = new Customer(); //Must allocate or bu is empty
	while(userFile.read(reinterpret_cast<char *> (bu), sizeof(BaseUser))) {
		if(bu->getID() == usrID) 
			return bu;
	}
}



/**
 * Gets next available ID for users
 */
int getNextID() {
	instream inFile;
	inFile.open("logins.dat",ios::binary);
	if(!inFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened. Press any key to continue.";
		return 0;
	}
	Login log;

	//Lowest ID is 900000
	int nextID = 900000;

	//Find next ID by taking highest + 1
	while(inFile.read(reinterpret_cast<char *> (&log), sizeof(Login))) {
		if(log.getID() > nextID) 
			nextID = log.getID() + 1;
	}
	inFile.close();
	return nextID;
}


/**
 * Allows the user to enter password without it appearing in the terminal
 */
string enter_password() {
	cout << "\nEnter a password and press enter: ";
	char c;
	string pass = "";
	while((c = getch()) != '\r') {
		pass += c;
	}
	pass = encrypt(pass);
	return pass;
}



/**
 * Creates user account
 */
void create_user_account() {
	cout << endl << "\t**Create a new user account**";
	cout << endl << "Enter First Name: ";
	string fname;
	cin >> fname;

	cout << endl << endl << "Enter Last Name: ";
	string lname;
	cin >> lname;

	//Use helper function to figure out next available ID
	int id;
	if(!(id = getNextID())) {
		cout << "\nUser creation failed. Press any key to continue.\n";
		return;
	}

	//Add user to user list
	BaseUser* newUser = new Customer(fname,lname,id);

	ofstream outFile;
	outFile.open("users.dat",ios::app|ios::binary);
	if(!outFile)
	{
		cout << "Something went wrong, users.dat couldn't be opened. Press any key to continue.";
		return;
	}

	//Find end of file
	outFile.seekp(0,ios::end);
	outFile.write(reinterpret_cast<char *> (newUser), sizeof(BaseUser));
	outFile.close();

	//Create and save password
	string pass = enter_password();

	//Create new login object to save to file
	Login log(id,pass);

	//Save login object to file
	ofstream outFile;
	outFile.open("logins.dat",ios::app|ios::binary);
	if(!outFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened. Press any key to continue.";
		return;
	}
	outFile.seekp(0,ios::end);
	outFile.write(reinterpret_cast<char *> (&log), sizeof(Login));
	outFile.close();

	cout << endl << "\tAccount Created";
}


/**
 * 
 */
void delete_account(int n) //delete an account
{
	account acc;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout << "Something went wrong, the File couldn't be opened. Press any key to continue";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		if(acc.retact_num() != n)
		{
			outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << endl << endl << "\tAccount Deleted";
}


/**
 * 
 */
void deposit_withdraw(int x, int choice) //figured I'd put deposit and withdraw in the same function for simplicities sake
{
	int amt;
	bool b = false;
	account acc;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout << "Something went wrong, the file couldn't be opened. Press any key to continue";
		return;
	}
	while(!File.eof() && b == false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if(acc.retact_num() == x)
		{
			acc.display_account();
			if(choice == 1)
			{
				cout << endl << endl << "\tDepositing";
				cout << endl << endl << "Enter Amount to be Deposited";
				cin >> amt;
				acc.deposit(amt);
			}
			if(choice == 2)
			{
				cout << endl << endl << "\tWithdrawing";
				cout << endl << endl << "Enter Amount to be Withdrawn";
				cin >> amt;
				int bal = acc.retdeposit() - amt;
				if((bal < 0 && acc.rettype() == 'S') || (bal < 0 && acc.rettype() == 'C'))
					cout << "Insufficience Balance";
				else
					acc.withdraw(amt);
			}
			int pos = (-1)*static_cast<int>(sizeof(acc));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(account));
			cout << endl << endl << "\tAccount Updated";
			b = true;
	       }
         }
	File.close();
	if(b == false)
		cout << endl << endl << "We Couldn't Find the Record, Please Try Again";
}


/**
 * 
 */
void display_account(int x) //read record from file
{
	account acc;
	bool b = false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout << "Something went wrong, the File couldn't be opened. Press any key to continue";
		return;
	}
	cout << endl << "Balance" << endl;
    while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		if(acc.retact_num() == x)
		{
			acc.display_account();
			b = true;
		}
	}
	inFile.close();
	if(b == false)
	cout << endl << endl << "That Account Number does not exist";
}


/**
 * 
 */
void display_all() //allows the user to see all their accounts
{
	account acc;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout << "Something went wrong, the File couldn't be opened. Press any key to continue";
		return;
	}
	cout << endl << endl << "\t\tAccount List" << endl << endl;
	cout << "Account Number      NAME           Type  Balance" << endl << endl;
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		acc.report();
	}
	inFile.close();
}


/**
 * 
 */
void edit_account(int x) //used to edit a record
{
	bool b = false;
	account acc;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout << "Something went wrong, the File couldn't be opened. Press any key to continue";
		return;
	}
	while(!File.eof() && b == false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if(acc.retact_num() == x)
		{
			acc.display_account();
			cout << endl << endl << "Enter New Account Info" << endl;
			acc.edit();
			int pos = (-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(account));
			cout << endl << endl << "\t Account Updated";
			b = true;
		  }
	}
	File.close();
	if(b == false)
		cout<< endl << endl << "We Couldn't Find the Record, Please Try Again";
}


/**
 * 
 */
void write_account() //write to file
{
	account acc;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	acc.create_account();
	outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
	outFile.close();
}
