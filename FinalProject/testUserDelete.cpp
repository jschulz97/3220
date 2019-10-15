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

bool delete_user_account(BaseUser* user);
void write_user_to_file(BaseUser* user);
BaseUser* get_user_from_file(int id);

/**
 * 
 */
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
			outFile << input + line << endl;
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
 */
void write_user_to_file(BaseUser* usr) {
	delete_user_account(usr);
	ofstream of("users.dat",ios::app);
	if(!of) {cout << "didnt open file";};

	if(usr->getID() == 100000) {
		ofstream of("users.dat",ios::app);

	}
	else {
		cout << "\nInside customer print";
		Customer *user = static_cast<Customer*>(usr);
		
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
	of.close();
}


/**
 *
 */
BaseUser* get_user_from_file(int id) {
	ifstream is("users.dat");
	if(!is) {cout << "could not open file";};
	string input;
	while(is >> input) {
		cout << "\nCheck if: " << endl << input << endl << to_string(id);
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
			cout << "\nNOPE";
			//advance file pointer to next line
			string temp;
			/*do {
				is >> temp;
			} while(temp != "|");*/
			getline(is,temp);
			cout << "\nThis is getline: " <<  temp;
		}
	}
	cout << "\nUnable to get user from file";
	is.close();
	return NULL;
}


int main() {

	BaseUser* cust = new Customer("Jeff","Schulz",900015);
	static_cast<Customer*>(cust)->myCheckings = new Checkings(123456,2000,true,1);
	static_cast<Customer*>(cust)->mySavings = new Savings(654321,4500,true,5,.01,4);

	BaseUser* cust2 = new Customer("Andy","Kirk",900020);
	BaseUser* cust3 = new Customer("Andy","Kirk",900021);	

	write_user_to_file(cust2);
	write_user_to_file(cust);
	write_user_to_file(cust3);

	Customer *user = new Customer();
	user = static_cast<Customer*>(get_user_from_file(900015));
	if(user) {

	cout << " " <<  user->mySavings->get_type() << " " <<  user->mySavings->get_act_num() << " " 
					<<  user->mySavings->get_balance() << " " <<  user->mySavings->approved << " " 
					<<  user->mySavings->get_mon() << " " <<  user->mySavings->get_int_rate() << " " 
					<<  user->mySavings->get_trans();
	cout << " " <<  user->myCheckings->get_type() << " " <<  user->myCheckings->get_act_num() << " " 
					<<  user->myCheckings->get_balance() << " " <<  user->myCheckings->approved
					<< " " <<  user->myCheckings->get_card_status();}


	return 0;
}