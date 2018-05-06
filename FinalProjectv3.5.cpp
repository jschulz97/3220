//============================================================================
// Name        : FinalProjectv3.5.cpp
// Author      : Andrew Kirkham, Jeff Schulz
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
bool delete_user_account(BaseUser*);
void display_all_accounts();
void approve_pending_accounts(BaseUser*);

int main()
{
	system("cls");
	cout << endl << "\t!!! Welcome to S&K Bank !!!";
	BaseUser* usr = new Customer();

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
				for(auto i : id) {
					if(!isdigit(i))
						throw error("Invalid user ID");
				}

				idnum = stoi(id);

				string password = enter_password();

				usr = sign_in(idnum,password);
			}
		} catch(error e) {
			e.display();
		}

	} while(usr->getID() == 1); //default value for new BaseUser


	if(usr->getID() != 1) {
		char choice;
		int num;
		do {
			if(usr->get_permissions() == 2) { //Menu for Bank Manager
				Manager *user = static_cast<Manager*>(usr);
				system("cls");
				cout << endl << endl << "\t----------MANAGER MODE----------";
				cout << endl << "\nWelcome back " << user->getFName();
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
					display_all_accounts();
					break;
				case '2':
					display_all_accounts();
					cout << "\n\nType the user ID # of the account to delete: ";
					int num;
					cin >> num;
					delete_user_account(get_user_from_file(num));
					break;
				case '3':
					approve_pending_accounts(user);
					break;
				case '0':
					break;
				 default:
					 cout << "\a\nIncorrect Input\n";
				}
				cout << "\n\n\tPress any key to continue";
				cin.ignore();
				cin.get();
				system("cls");

			} else { //Menu for regular customers
				Customer *user = static_cast<Customer*>(usr);
				system("cls");
				cout << endl << "\t!!! Welcome " << user->getFName() << " !!!";
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
				case '1': //View account balances
					user->display_account_details();
					break;
				case '2': //Deposit
					user->deposit();
					write_user_to_file(user);
					break;
				case '3': //Withdraw
					user->withdraw();
					write_user_to_file(user);
					break;
				case '4': //Create a new savings/checkings account (only if the user does not already have one or both)
					user->add_account();
					write_user_to_file(user);
					break;
				case '5': //Edit account details
					user->edit_account();
					write_user_to_file(user);
					break;
				case '0':
					break;
				 default:
					 cout << "\a\nIncorrect Input\n";
				}
				cout << "\n\n\tPress any key to continue";
				cin.ignore();
				cin.get();
				system("cls");
			}

		}
		while(choice != '0');
		cout << "\nThanks for banking with S&K!\n\n";
	}
	return 0;
}



/**
 * Sign in a user using the logins file. Returns the user object pointer.
 */
BaseUser* sign_in(int usrID, string encrypted_pass) {
	//Open logins.dat
	ifstream loginFile;
	loginFile.open("logins.dat");
	if(!loginFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened in sign_in(). Press any key to continue.";
		return new Customer();
	}

	//See if password matches one in file
	bool found = false;
	string word;
	while(loginFile >> word) {
		if(stoi(word) == usrID) {
			found = true;
			//cout << endl << "AA" << log->getPass() << "AA";
			string p;
			loginFile >> p;
			if(encrypted_pass != p) {
				cerr << "\nPassword is incorrect\n";
				return new Customer();
			}
		}
		string temp;
		getline(loginFile,temp);
	}
	loginFile.close();

	if(!found) {
		cout << "\nUser does not exist. Press any key to continue.";
		return new Customer();
	}


	//Find user data, return user object pointer
	return get_user_from_file(usrID);
}



/**
 * Gets next available ID for users by analyzing the logins file
 */
int getNextID() {
	ifstream inFile;
	inFile.open("logins.dat");
	if(!inFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened. Press any key to continue.";
		inFile.close();
		return 0;
	}

	//Lowest ID is 900000
	int nextID = 900000;

	//Find next ID by taking highest + 1
	string word;
	while(inFile >> word) {
		if(stoi(word) >= nextID) {
			nextID = stoi(word) + 1;
		}
		string temp;
		getline(inFile,temp);
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
	//cout << endl << "AA" << pass << "AA";
	pass = encrypt(pass);
	//cout << endl << "AA" << pass << "AA";
	return pass;
}



/**
 * Creates user account, writes user object to users file, and creates their login
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
		cout << "\nUser creation failed in create_user_account() & getNextID(). Press any key to continue.\n";
		return;
	}
	cout << "\nYour user ID will be: " << id;

	//Make new user - will always be a customer
	BaseUser* newUser = new Customer(fname,lname,id);

	//Self explanatory
	write_user_to_file(newUser);

	//Create and save password
	string pass = enter_password();

	//Save login object to file
	ofstream outFile;
	outFile.open("logins.dat",ios::app);
	if(!outFile)
	{
		cout << "Something went wrong, logins.dat couldn't be opened in create_user_account(). Press any key to continue.";
		return;
	}
	outFile << endl << id << " " << pass;
	outFile.close();

	cout << endl << "\n\tAccount Created. User ID: " << id;
}


/**
 * Displays the balances of the current user's accounts
 */
void display_balances(BaseUser* usr) {
	Customer* cust = static_cast<Customer*>(usr);
	if(!(cust->myCheckings == NULL)) {
		cust->myCheckings->display_details();
	}
	if(!(cust->mySavings == NULL)) {
		cust->mySavings->display_details();
	}
}


/**
 * Writes a user object to the users file
 */
void write_user_to_file(BaseUser* usr) {
	delete_user_account(usr);
	ofstream of("users.dat",ios::app);
	if(!of) {cerr << "\nCould not open file users.dat in write_user_to_file()";};

	if(usr->getID() == 100000) {
		ofstream of("users.dat",ios::app);

	}
	else {
		//cout << "\nInside customer print";
		Customer *user = static_cast<Customer*>(usr);

		of << user->getID() << " " << user->getFName() << " " << user->getLName();
		if(user->mySavings != NULL) {
			//cout << "\nPrinting Savings";
			of << " " <<  user->mySavings->get_type() << " " <<  user->mySavings->get_act_num() << " "
				<<  user->mySavings->get_balance() << " " <<  user->mySavings->approved << " "
				<<  user->mySavings->get_mon() << " " <<  user->mySavings->get_int_rate() << " "
				<<  user->mySavings->get_trans();
		}
		if(user->myCheckings != NULL) {
			//cout << "\nPrinting Checkings";
			of << " " <<  user->myCheckings->get_type() << " " <<  user->myCheckings->get_act_num() << " "
				<<  user->myCheckings->get_balance() << " " <<  user->myCheckings->approved
				<< " " <<  user->myCheckings->get_card_status();
		}
		of << endl;
	}
	of.close();
}


/**
 * Retrieves user object from the users file
 */
BaseUser* get_user_from_file(int id) {
	ifstream is("users.dat");
	if(!is) {cout << "\nCould not open file users.dat in get_user_from_file()";};
	string input;
	while(is >> input) {
		//cout << "\nCheck if: " << endl << input << endl << to_string(id);
		if(input == to_string(id)) {
			if(input == "100000") {
				string fn,ln;
				is >> fn;
				is >> ln;
				Manager *man = new Manager(fn,ln);
				is.close();
				return man;
			} else {
				int id,act,mon,tr,card;
				string fn,ln;
				double bal,inter;
				bool app;
				is >> fn >> ln;
				id = stoi(input);
				Customer *c = new Customer(fn,ln,id);

				string temp;
				is >> temp;
				if(temp == "Savings") {
					is >> act >> bal >> app >> mon >> inter >> tr;
					c->mySavings = new Savings(act,bal,app,mon,inter,tr);
					is >> temp;
				}
				if(temp == "Checkings") {
					is >> act >> bal >> app >> card;
					c->myCheckings = new Checkings(act,bal,app,card);
				}
				is.close();
				return c;
			}
		} else {
			//advance file pointer to next line
			string temp;
			/*do {
				is >> temp;
			} while(temp != "|");*/
			getline(is,temp);
			//cout << "\nThis is getline: " <<  temp;
		}
	}
	cout << "\nUnable to get user from file";
	is.close();
	return NULL;
}


/**
 * Deletes a specific user from the records
 */
bool delete_user_account(BaseUser* user) //delete an account
{
	ifstream inFile;
	ofstream outFile;
	inFile.open("users.dat");
	if(!inFile)
	{
		cout << "Something went wrong, the File users.dat couldn't be opened. Press any key to continue";
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
			outFile << input + line << endl;
		}
	}
	inFile.close();
	outFile.close();
	remove("users.dat");
	rename("temp.dat", "users.dat");

	inFile.open("logins.dat");
	if(!inFile)
	{
		cout << "Something went wrong, the File users.dat couldn't be opened. Press any key to continue";
		return false;
	}
	outFile.open("temp.dat");
	inFile.seekg(0,ios::beg);

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
			outFile << input + line << endl;
		}
	}
	inFile.close();
	outFile.close();
	remove("logins.dat");
	rename("temp.dat", "logins.dat");

	if(del){
		return true;
	} else {
		return false;
	}
}


/**
 * yes
 */
void display_all_accounts() {
	ifstream logins("logins.dat");
	Customer *cust = new Customer();

	string word;
	while(logins >> word) {
		if(stoi(word) != 100000) {
			cust = static_cast<Customer*>(get_user_from_file(stoi(word)));
			cout << endl << endl << cust->getID() << " - " << cust->getFName() << " " << cust->getLName();
			if(cust->mySavings != NULL) {
				cout << endl << endl << "\tSavings: #" <<  cust->mySavings->get_act_num()
					<< "\n\tBalance: " << cust->mySavings->get_balance()
					<< "\n\tInterest Rate: " << cust->mySavings->get_int_rate() 
					<< "\n\tTransactions left in month: " << cust->mySavings->get_trans();
			}
			if(cust->myCheckings != NULL) {
				cout << endl << endl << "\tCheckings: #" <<  cust->myCheckings->get_act_num()
					<< "\n\tBalance: " << cust->myCheckings->get_balance()
					<< "\n\tDebit card status: " << cust->myCheckings->get_card_status();
			}
		}
		string temp;
		getline(logins,temp);
	}

	logins.close();
}


/**
 *
 */
void approve_pending_accounts(BaseUser *manager) {
	ifstream logins("logins.dat");
	Customer *cust = new Customer();
	vector<BaseUser*> savingsVec;
	vector<BaseUser*> checkingsVec;

	string word;
	while(logins >> word) {
		if(stoi(word) != 100000) {
			cust = static_cast<Customer*>(get_user_from_file(stoi(word)));
			if(cust->mySavings != NULL) {
				if(!(cust->mySavings->approved)) {
					cout << endl << endl << cust->getID() << " - " << cust->getFName() << " " << cust->getLName();
					savingsVec.push_back(cust);
					cout << endl << "\tSavings";
				}
			}
			if(cust->myCheckings != NULL) {
				if(!(cust->myCheckings->approved)) {
					cout << endl << endl << cust->getID() << " - " << cust->getFName() << " " << cust->getLName();
					checkingsVec.push_back(cust);
					cout << endl << "\tCheckings";
				}
			}
		}
		string temp;
		getline(logins,temp);
	}

	cout << "\n\nApprove all? (Y/N): ";
	char c;
	cin >> c;
	if(c == 'y' || c == 'Y') {
		for(auto i : savingsVec) {
			static_cast<Customer*>(i)->mySavings->approve(manager);
			write_user_to_file(i);
		}
		for(auto i : checkingsVec) {
			static_cast<Customer*>(i)->myCheckings->approve(manager);
			write_user_to_file(i);
		}
	}


	logins.close();
}
