/*
 * BinRep.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: jtsmbb
 */

#include <iostream>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <climits>

using namespace std;

int main() {

	unsigned short input;

	cout << "Enter a number: " ;
	cin >> input;

	while(input < 0 || input > 65535) {
		cout << "Input must be between 0 and 65535. Enter again: ";
		cin >> input;
	}

	cout << "\n\nTETSTESTSETRSETTESTESTESSTEE\n\n";

	cout << "\n\nMORE TESTING\n\n";

	cout << "Compute using: \na. Arithmetic operations\nb. Bitwise operations\n";
	char ans;
	cin >> ans;

	switch(ans) {
		case 'a': //Arithmetic
			{short count = 0;
			double total = 0;
			while(input > 0) {
				total = total + pow(10.0,count)*(input%2);
				input /= 2.0;
				count++;

			}
			cout << endl << setfill('0') << setw(16) << setprecision(16) << total;
			break;}

		case 'b': //Bitwise
			{unsigned int mask = 32768;
			while(mask > 0) {
			   if((input & mask) == 0 )
			         cout << "0";
			   else
			         cout << "1";
			  	mask = mask >> 1 ;  //Right Shift
			}

			break;}

		default:
			cout << "\nInvalid input, exiting...\n";
			break;
	}

	cout << endl;

	return 0;
}


