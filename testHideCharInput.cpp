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

int main() {
	char c;
	string word = "";
	/*do {
		c = getch();
		word += c;
	} while(c != '\r');*/

	while((c = getch()) != '\r') {
		word += c;
	}

	word[word.length()] = '5';
	cout << endl << word << endl;
}