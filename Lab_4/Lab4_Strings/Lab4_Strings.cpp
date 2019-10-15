// Lab4_strings.cpp
// Author: Jeffrey Schulz

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++11
//      or:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++0x
// Some initialization methods and other things are not supported by the old standard. 

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Complete the assignments stated in the comments.
int main()
{
// ****************************************************************************
// Declare and initialize four or five strings. Use different ways of
// initializing, as shown in Table 7.1 (Lecture 7). 
// Try all the operations in Table 7.2 (Lecture 7) using the strings that
// you declared.
// ****************************************************************************

	string s1;
	string s2("test_value");
	string s3(s2);
	string s4 = "another test value";
	string s5(5,'x');

	cout << s2 << endl;
	cout << endl;

	cout << "Enter a string: ";
	getline(cin,s1);
	cout << endl;

	cout << endl << "Enter a second string: ";
	cin >> s3;
	cout << endl;

	cout << endl << "s5: " << s5 << endl << "Is s5 empty? " << s5.empty() << endl;
	cout << "s5 is " << s5.size() << " character(s) long.\n";
	cout << endl;

	s5[2] = 'T';
	cout << "s5[2] = 'T'" << endl << "s5: " << s5 << endl;
	cout << endl;

	s1 = s2+s5;
	cout << "s1 = s2+s5" << endl << "s1: " << s1 << endl;
	cout << endl;

	s5 = s1;
	cout << "s5 = s1" << endl << "s5: " << s5 << endl;
	cout << endl;

	cout << s2 << endl;
	cout << s3 << endl;
	cout << "s2 and s3 equal?" << endl;
	cout << (s2 == s3);
	cout << endl << endl;
	cout << "s2 and s3 not equal?" << endl << (s2 != s3);
	cout << endl << endl;

	cout << "s5 > s2" << endl << (s5 > s2) << endl;
	cout << endl << "------------------------------------------------------" << endl;

// -----------------------------------------------------------------------
	string line;
	cout << "\nEnter some text:" << endl;
	cin.ignore();
	getline(cin,line);
	cout << line << endl << endl;

// ****************************************************************************
// Use "Range for" loops (L7_Ex6_Strings.cpp) and operations in table 7.3 to:
// 1) Count the number of letters in your input line above;
// 2) Count the number of digits;
// 3) Count the number of words (may be separated by white spaces, dots, etc.);

// 4) change the case of the letters (upper to lowercase and vice-versa).
// 5) Replace any whitespace with a dot ('.').
// Print the converted text in 4) and 5)
// ****************************************************************************

	int let = 0, dig = 0, words = 0;
	char prev = ' ';

	for(auto i:line) {
		if(isalpha(i)) {
			let++;
		}
		if(isdigit(i)) {
			dig++;
		}
		if((ispunct(prev) || isspace(prev)) && isalnum(i)) {
			words++;
		}
		prev = i;
	}

	cout << "letters: " << let << endl;
	cout << "digits: " << dig << endl;
	cout << "words: " << words << endl << endl;

	cout << "line: " << line << endl << "Switched cases: " << endl;

	int cnt = 0;
	for(auto i:line) {
		if(islower(i)) {
			i = toupper(i);
			line[cnt] = i;
		}
		else if(isupper(i)) {
			i = tolower(i);
			line[cnt] = i;
		}
		cnt++;
	}

	cout << line << endl << endl;

	cnt = 0;
	for(auto i:line) {
		if(isspace(i)) {
			line[cnt] = '.';
		}
		cnt++;
	}

	cout << "Replaces spaces with '.': " << endl << line << endl << endl;

	return 0;
}
