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
	/*ofstream out;
	out.open("users.dat",ios::app|ios::binary);
	BaseUser* usr = new Manager("Stevie","Wonder");
	out.write(reinterpret_cast<char *> (usr), sizeof(BaseUser));
	out.close();*/

	ofstream out;
	out.open("logins.dat",ios::app|ios::binary);
	cout << "uhhhuh";
	Login log = Login(100000,encrypt("bankingrox"));
	cout << "yes";
	out.write(reinterpret_cast<char *> (&log), sizeof(Login));
	cout << " no";
	out.close();
	return 0;
}
