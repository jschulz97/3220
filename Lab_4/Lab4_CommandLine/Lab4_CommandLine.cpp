// Lab4_CommandLine.cpp
// Author: Luis Rivera

#include <iostream>
#include <string>
using namespace std;

// argc will hold the number of input parameters, including the program name
// argv is an array of pointers to char (C-strings). argv[0] is a C-string holding
// the program name (the way it's called in the terminal)
// Try calling the program without parameters, with one parameter, two, etc.
// Compare the two approaches.
int main(int argc, char *argv[])
{
	int i = 0, count;

// --- C-like approach --------------------------------------------------------
	while(i < argc){
		cout << "argv[" << i << "] = " << argv[i] << endl;
			
		count = 0;
		while(argv[i][count++] != '\0');
		cout << "#of characters (not including string termination char.): "
			 << count-1 << endl << endl;
		i++;
	}
	
	cout << endl;
	
// --- Using a C++ string -----------------------------------------------------
	i = 0;
	string argstr;
	while(i < argc){
		argstr = string(argv[i]); // convert the C-string into a string
		cout << "argv[" << i << "] = " << argstr << endl;
			
		count = argstr.size();
		cout << "#of characters: " << count << endl << endl;
		i++;
	}
	
	return 0;
}