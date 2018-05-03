#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<conio.h>

#include "Users&Accounts.h"
//#include "Users.h"
#include "Encrypt.h"
//#include "Loan.h"
using namespace std;

string enter_password();

int main() {
	ofstream out("users.dat",ios::binary);
	//out.open("users.dat");
	Manager usr = Manager("Stevie","Wonder");
	out.write(reinterpret_cast<char *> (&usr), sizeof(BaseUser));
	out.close();

	ofstream outs("logins.dat",ios::binary);
	//out.open("logins.dat");
	Login log = Login(100000,encrypt("bankingrox"));
	outs.write(reinterpret_cast<char *> (&log), sizeof(Login));
	outs.close();
	cout << "\nDONE\n";
	return 0;
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
	cout << endl << "AA" << pass << "AA";
	pass = encrypt(pass);
	cout << endl << "AA" << pass << "AA";
	return pass;
}