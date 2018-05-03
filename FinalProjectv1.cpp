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

#include<Accounts.h>
#include<Users.h>
#include<Encrypt.h>
#include<Loan.h>
using namespace std;

/**************************************************************************************************/


/****************************************************************************************************/

void delete_account(int);
void deposit_withdraw(int, int);
void display_account(int);
void display_all();
void edit_account(int);
void write_account();

int main()
{
	cout << endl << "\t!!!Welcome to S&K Bank!!!";
	BaseAccount User*;

	//Log in loop
	do {
		try {
			cout << endl << "Enter your user ID or 'N' to create a new account: ";
			string id;
			cin >> id;
			if(id == "N") {
				create_account();
			}

			//Check if id is a number
			//int pow = 0;
			int idnum;
			for(auto i : id) {
				if(!isdigit(i)) 
					throw error("Invalid user ID");
			}

			//Convert id string to int
			idnum = atoi(id);

			User = sign_in(idnum,pass);
		} catch(error e) {

		}

	} while(User->getID() == 1);


	{
		char choice;
		int num;
		do
		{
			system("cls");
			cout << endl << "\t!!!Welcome ";
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
		while(choice != '8');
	}
	return 0;
}



/**
 * 
 */
BaseAccount* sign_in(string usr, string encrypted_pass) {

}




/**
 * 
 */
void Savings::create_account()
{
	cout << endl << "**Create a new account**";
	cout << endl << "Enter Account Number: ";
	cin >> act_num;
	cout << endl << endl << "Enter Name: ";
	cin.ignore();
	cin.getline(act_name,50);
	cout << endl << "What Type of Account do you want to open? (C for Checkings, S for Savings): ";
	cin >> act_type;
	act_type=toupper(act_type);
	cout << endl << "Enter Initial Amount: ";
	cin >> dep;
	cout << endl << "Account Created";
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
