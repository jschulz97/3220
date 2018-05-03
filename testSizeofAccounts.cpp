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
	BaseUser* 	b1 = new Customer("fred","duever");
	BaseUser* 	b2 = new Manager("jacob","smith");
	Customer	c1 = Customer("jeremy","colozza");
	Manager		m1 = Manager("charlie","renner");

	cout << setw(10) << "\nc1:" << setw(10) << "\tm1:";
	cout << endl << setw(10) << sizeof(c1) << setw(10) << "\t" << sizeof(m1);

	cout << setw(10) << "\nb1:" << setw(10) << "\tb2:";
	cout << endl << setw(10) << sizeof(*b1) << setw(10) << "\t" << sizeof(*b2);

	cout << endl << "b1.getID():\t" << b1->getID();
	cout << endl << "b2.getID():\t" << b2->getID();
	cout << endl << endl;
}