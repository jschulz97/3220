// Lab4_Files.cpp
// Author: Luis Rivera

// To use the new standard, YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG:
//		-std=c++11  OR  -std=c++0x
// 		g++ Lab4_Files.cpp -o Lab4_Files -std=c++11
//  or: g++ Lab4_Files.cpp -o Lab4_Files -std=c++0x

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <cctype>
#include <cstdlib>
using namespace std;

// The program expects two input parameters, like this:
// ./Lab4_Files -n 1
// It will then try to open a file named Lab4_read_n.txt, where n is the last input.
// Use the file Lab4_read_01.txt provided on Canvas.
// Compare the two approaches of opening and manipulating files (C vs. C++)
// In this simple example there are some hard-coded values. You should avoid those.
// in your programs. How can you make the program more flexible in that sense?
int main(int argc, char *argv[])
{
	int n;
	if(argc == 3){
		if((argv[1][0] == '-') && (argv[1][1] == 'n')) {
            n = atoi(argv[2]);
            cout << "n value: " << n << endl;
		}
		else {
			cout << "Wrong option: " << argv[1] << endl;
			return 1;
		}
	}
	else {
		cout << "Invalid number of input arguments: " << argc << endl;
		cout << "\nUsage: " << argv[0] << " -n IntValue " << endl << endl;
		return 1;
	}

// --- Using *FILE and C functions --------------------------------------------
	FILE *fp_r, *fp_w;
	char filename[50]; // 49 characters should be enough. Use a bigger array, if not.
	int i, datain[6];  // fixed size.
					   // What if the size is not known beforehand?

	sprintf(filename, "Lab4_read_%02d.txt", n);
	fp_r = fopen(filename,"r");  // open for reading
	
	// check if the file was successfully opened
	if(fp_r == NULL) {
		perror("Error opening file");	// good thing to check for errors
		return 1;
	}
	
	for(i = 0; i < 6; i++) { // Avoid hard coding the values. What if
					// there are more or less than 6 values in the file?
		fscanf(fp_r, "%d", datain+i); // same: &datain[i]
	}
	fclose(fp_r);	// Close the file
		
	sprintf(filename, "Lab4_write_%02d.txt", n);
	fp_w = fopen(filename,"w");
	
	// check if the file was successfully opened
	if(fp_w == NULL) {
		perror("Error opening file");
		return 1;
	}
	
	for(i = 0; i < 6; i++) {	// Avoid hard coding
		fprintf(fp_w, "Data %d:\t%d,\t%.2f,\t%X\n",
				i, datain[i], 0.5+datain[i], datain[i]);
	}
	fclose(fp_w);	// Close the file
	
	printf("Done! (C style)\n");

// --- Using fstream (C++) ----------------------------------------------------
	ifstream inFS;	// input file stream
	ofstream outFS;	// output file stream
	string myFile = "Lab4_read_0" + to_string(n) + ".txt";
	// What if the number entered has 2 digits?
	// You could use the C-string filename and sprintf
	
	// Open fi << endl << endl;
	inFS.open(myFile);	// in the old standard (before C++11), you need myFile.c_str();
    
	// check if the file was successfully opened
	if(!inFS.is_open()) {
		cerr << "Could not open the file " << myFile << endl;
		return 1;
	}
	
	i = 0;
	while(!inFS.eof()) {	// check until reaching the end of the file
		inFS >> datain[i++];	// similar to cin >>. Careful with the data types
	}
	inFS.close();	// Close the file
	
	myFile = "Lab4_writeC++_0" + to_string(n) + ".txt";
	// Open file to be written to
	outFS.open(myFile); // again, use myFile.c_str() if not using the new standard
	
	// check if the file was successfully opened
	if(!outFS.is_open()) {
		cerr << "Could not open file " << myFile << endl;
		return 1;
	}
	
	for(i = 0; i < 6; i++) {	// Avoid hard coding
		// similar to cout <<
		outFS << "Data " << dec << i << ":\t" << datain[i] << ",\t"
			  << setprecision(2) << fixed << 0.5+datain[i] << ",\t"
			  << uppercase << hex << datain[i] << endl;
	}
	outFS.close();	// Close the file
	
	cout << "Done! (C++ style)" << endl;
	
	return 0;
}
