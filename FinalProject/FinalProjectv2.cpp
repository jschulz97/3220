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
//#include<conio.h> //For hiding password with getch()
#include<cmath>

#include "Users&Accounts.h"
#include "Encrypt.h"
//#include "Loan.h"
using namespace std;

/**************************************************************************************************/


/****************************************************************************************************/

string enter_password();
void create_user_account();
void display_balances(BaseUser*);
BaseUser* sign_in(int,string);
void write_user_to_file(BaseUser*);
BaseUser* get_user_from_file(int id);

void delete_user_account(BaseUser*);
/*void display_account(int);
void edit_account(int);
void write_account();*/

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
			} else {
				//Check if id is fully a number
				int idnum = 0;
				int power = 5;
				for(auto i : id) {
					if(!isdigit(i)) 
						throw error("Invalid user ID");
					idnum += atoi(&i)*pow(10,power--);
				}

				string password = enter_password();

				User = sign_in(idnum,password);
			}
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
				cout << endl << endl << "\t----------MANAGER MODE----------";
				cout << endl << "\tWelcome back " << User->getFName();
				cout << endl << endl << "0) Exit";
				cout << endl << endl << "1) Display all accounts";
				cout << endl << endl << "2) Close a user account";
				cout << endl << endl << "3) Approve new bank accounts";
				cout << endl << endl << "Make Your Choice (0-3): ";
				cin >> choice;
				system("cls");
				switch(choice)
				{
				case '1':
					
					break;
				case '2':
					
					break;
				case '3':
					
					break;
				 default:
					 cout << "\a";
				}
				cin.ignore();
				cin.get();

			} else { //Menu for regular customers

				system("cls");
				cout << endl << "\t!!!Welcome " << User->getFName() << "!!!";
				cout << endl << endl << "0) Exit";
				cout << endl << endl << "1) View Balances";
				cout << endl << endl << "2) Deposit";
				cout << endl << endl << "3) Withdraw";
				cout << endl << endl << "4) New Account";
				cout << endl << endl << "5) Edit User Account Details";
				cout << endl << endl << "Make Your Choice (0-5): ";
				cin >> choice;
				system("cls");
				switch(choice)
				{
				case '1':
					display_balances(User);
					break;
				case '2':
					
					break;
				case '3':
					
					break;
				case '4':
					
					break;
				case '5':
					
					break;
				 default:
					 cout << "\a";
				}
				cin.ignore();
				cin.get();
			}

		}
		while(choice != '0');
		cout << "\nThanks for banking with S&K!\n\n";
	}
	return 0;
}



/**
 * 
 */
BaseUser* sign_in(int usrID, string encrypted_pass) {
	ifstream loginFile;
	loginFile.open("logins.dat",ios::binary);
	if(!loginFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened. Press any key to continue.";
		return new Customer();
	}
	
	Login* log = new Login(1,"1");
	bool found = false;
	while(loginFile.read(reinterpret_cast<char *> (log), sizeof(Login))) {
		if(log->getID() == usrID) {
			found = true;
			//cout << endl << "AA" << log->getPass() << "AA";
			if(encrypted_pass != log->getPass()) {
				cerr << "\nPassword is incorrect\n";
				return new Customer();
			}
		}
	}
	loginFile.close();

	if(!found) {
		cout << "\nUser does not exist. Press any key to continue.";
		return new Customer();
	}

	ifstream userFile;
	userFile.open("users.dat",ios::binary);
	if(!userFile)
	{
		cout << "Something went wrong, users.dat couldn't be opened. Press any key to continue.";
		return new Customer();
	}

	if(usrID == 100000) {
		BaseUser* bu = new Manager(); //Must allocate or bu is empty
		while(userFile.read(reinterpret_cast<char *> (bu), sizeof(BaseUser))) {
			if(bu->getID() == usrID) 
				return bu;
		}
	} else {
		BaseUser* bu = new Customer(); //Must allocate or bu is empty
		while(userFile.read(reinterpret_cast<char *> (bu), sizeof(BaseUser))) {
			if(bu->getID() == usrID) 
				return bu;
		}
	}
	userFile.close();
}



/**
 * Gets next available ID for users
 */
int getNextID() {
	ifstream inFile;
	inFile.open("logins.dat");
	if(!inFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened. Press any key to continue.";
		return 0;
	}

	//Lowest ID is 900000
	int nextID = 900000;

	//Find next ID by taking highest + 1
	while(inFile.read(reinterpret_cast<char *> (log), sizeof(Login))) {
		cout << endl << log->getID();
		if(log->getID() >= nextID) {
			nextID = log->getID() + 1;
		}
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

	cin >> pass;

/*	while((c = getch()) != '\r') {
		pass += c;
	}
	cout << endl << "AA" << pass << "AA";
	pass = encrypt(pass);
	cout << endl << "AA" << pass << "AA";*/
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
	cout << "\nYour user ID will be: " << id;

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
	Login* log = new Login(id,pass);

	//Save login object to file
	outFile.open("logins.dat",ios::app|ios::binary);
	if(!outFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened. Press any key to continue.";
		return;
	}
	outFile.seekp(0,ios::end);
	outFile.write(reinterpret_cast<char *> (log), sizeof(Login));
	outFile.close();

	cout << endl << "\tAccount Created. User ID: " << id;
}


/**
 * Displays the balances of the current user's accounts
 */
void display_balances(BaseUser* usr) {
	Customer* cust = static_cast<Customer*>(usr);
	if(!(cust->myCheckings == NULL)) {
		cust->myCheckings->display_details();
		//cout << setw(20) << "Checkings #" << usr->myCheckings->get_act_num() << endl << 
			//setw(20) << usr->myCheckings->get_balance() << endl;
	}
	if(!(cust->mySavings == NULL)) {
		cust->mySavings->display_details();
	}
}


/**
 * 
 */
void write_user_to_file(BaseUser* usr) {
	delete_user_account(usr);
		if(usr->getID() == 100000) {
			ofstream of("users.dat",ios::app);

		}
		else {
			cout << "\nInside customer print";
			Customer *user = static_cast<Customer*>(usr);
			ofstream of("users.dat",ios::app);
			if(!of) {cout << "didnt open file";};
			of << user->getID() << " " << user->getFName() << " " << user->getLName();
			if(user->mySavings != NULL) {
				cout << "\nPrinting Savings";
				of << " " <<  user->mySavings->get_type() << " " <<  user->mySavings->get_act_num() << " " 
					<<  user->mySavings->get_balance() << " " <<  user->mySavings->approved << " " 
					<<  user->mySavings->get_mon() << " " <<  user->mySavings->get_int_rate() << " " 
					<<  user->mySavings->get_trans();
			}
			if(user->myCheckings != NULL) {
				cout << "\nPrinting Checkings";
				of << " " <<  user->myCheckings->get_type() << " " <<  user->myCheckings->get_act_num() << " " 
					<<  user->myCheckings->get_balance() << " " <<  user->myCheckings->approved
					<< " " <<  user->myCheckings->get_card_status();
			}
			of << endl;
		}
}


/**
 *
 */
BaseUser* get_user_from_file(int id) {
	
}


bool delete_user_account(BaseUser* user) //delete an account
{
	ifstream inFile;
	ofstream outFile;
	inFile.open("users.dat");
	if(!inFile)
	{
		cout << "Something went wrong, the File couldn't be opened. Press any key to continue";
		return false;
	}
	outFile.open("temp.dat");
	inFile.seekg(0,ios::beg);
	string input;
	bool del = false;
	while(inFile >> input)
	{
		if(input == to_string(user->getID()))
		{
			string temp;
			getline(inFile,temp);
			del = true;
		} else {
			string line;
			getline(inFile,line);
			outFile << line;
		}
	}
	inFile.close();
	outFile.close();
	remove("users.dat");
	rename("temp.dat", "users.dat");
	if(del){
		cout << endl << endl << "\tAccount Deleted";
		return true;
	} else {
		cout << endl << endl << "\tAccount Not Found";
		return false;
	}
}



/**
 * 
 *
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
}*/


/**
 * 
 *
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
}*/


/**
 * 
 *
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
}*/


/**
 * 
 *
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
}*/


/**
 * 
 *
void write_account() //write to file
{
	account acc;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	acc.create_account();
	outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
	outFile.close();
}*/
