#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string>
#include<cstdlib>
//#include<conio.h>

#include "Users&Accounts.h"
//#include "Users.h"
#include "Encrypt.h"
//#include "Loan.h"
using namespace std;

string enter_password();

int main() {
	ofstream out("users.dat");
	out << "900020 Andy Kirk\n900015 Jeff Schulz Savings 654321 4500 1 5 0.01 4 Checkings 123456 2000 1 1\n900021 Tom Smith\n100000 Stevie Wonder\n";	
	out.close();

	ofstream outs("logins.dat");
	outs << "900020 ##1\n900015 ##1\n900021 ##1\n100000 !|93/9+\n";

	outs.close();
	cout << "\nDONE\n";
	return 0;
}

/**
 * Allows the user to enter password without it appearing in the terminal
 *
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
}*/
