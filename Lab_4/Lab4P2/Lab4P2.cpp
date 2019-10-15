/*
 * Lab4P2.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: Jeffrey Schulz
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <cstdlib>
#include <cctype>

using namespace std;

int* openfile(int);
void error(void);
void help(void);
int offset(int* data, double off, int num);
int scale(int* data, double scl, int num);
int cpfile(int* data, string name);
double mean(int* data);
int max(int* data);
int center(int* data, int num);
int normalize(int* data, int num);
int getstats(int* data, int num);


int main(int argc, char *argv[]) {

	int* inputdata = NULL;
	int num = 0;
	double off = 0;
	double scl = 0;
	string newname = "";
	bool stats = false;
	bool cen = false;
	bool norm = false;

	if(argc == 1) {
		error();
		return 1;
	}

	for(int i=1; i<argc; i++) {
		//Check if a flag
		if(argv[i][0] == '-') {

			//Check if n, for the file number
			if(argv[i][1] == 'n') {
				if((i<argc-1) && (isdigit(argv[i+1][0]))) {
					num = atoi(argv[i+1]);
					inputdata = openfile(num);
					i++;
				} else {
					error();
					return 1;
				}
			}

			//Check if o, for the offset value
			else if(argv[i][1] == 'o') {
				if((i<argc-1) && (isdigit(argv[i+1][0]))) {
					off = atof(argv[i+1]);
					i++;
				} else {
					error();
					return 1;
				}
			}

			//Check if s, for the scale value
			else if(argv[i][1] == 's') {
				if((i<argc-1) && (isdigit(argv[i+1][0]))) {
					scl = atof(argv[i+1]);
					i++;
				} else {
					error();
					return 1;
				}
			}

			//Check if r, for a new name
			else if(argv[i][1] == 'r') {
				if((i<argc-1) && (isalnum(argv[i+1][0]))) {
					newname = argv[i+1];
					i++;
				} else {
					error();
					return 1;
				}
			}

			//Check if h, for displaying help
			else if(argv[i][1] == 'h') {
				help();
				return 0;
			}

			//Check if S, for getting average and max
			else if(argv[i][1] == 'S') {
				stats = true;
			}

			//Check if C, for centering the signal
			else if(argv[i][1] == 'C') {
				cen = true;
			}

			//Check if N, for normalizing the signal
			else if(argv[i][1] == 'N') {
				norm = true;
			}

			//Something isn't correct if input doesn't match one of these
			else {
				error();
				return 1;
			}
		} else {
			error();
			return 1;
		}
	}

	//If the flags were present, complete actions:

	if(off) {
		if(offset(inputdata, off, num))
			cout << "\nOffset completed successfully\n";
		else
			cout << "\nOffset Failed\n";
	}

	if(scl) {
		if(scale(inputdata, scl, num))
			cout << "\nScale completed successfully\n";
		else
			cout << "\nScale Failed\n";
	}

	if(newname != "") {
		if(cpfile(inputdata, newname))
			cout << "\nCopy file completed successfully\n";
		else
			cout << "\nCopy file failed\n";
	}

	if(stats) {
		if(getstats(inputdata,num))
			cout << "\nGet statistics completed successfully\n";
		else
			cout << "\nGet statistics failed\n";
	}

	if(cen) {
		if(center(inputdata,num))
			cout << "\nCenter data completed successfully\n";
		else
			cout << "\nCenter data failed\n";
	}

	if(norm) {
		if(normalize(inputdata,num))
			cout << "\nNormalize data completed successfully\n";
		else
			cout << "\nNormalize data failed\n";
	}

	return 0;
}


/**
 * Opens file number from the parameter, reads data into and returns int array
 */
int* openfile(int n) {
	string name;

	//Concatenate strings from input number to open correct data file
	if(n<10)
		name = "Raw_data_0" + to_string(n) + ".txt";
	else
		name = "Raw_data_" + to_string(n) + ".txt";

	//Declare and open file stream
	ifstream inFS;
	inFS.open(name);

	// check if the file was successfully opened
	if(!inFS.is_open()) {
		cerr << "Could not open the file " << name << endl;
		return NULL;
	}

	//Grabs first two integers of the file, the num of inputs and the max number
	int size,max;
	inFS >> size;
	inFS >> max;

	//Allocate memory for int array
	int* inputdata = new int[size+2];

	inputdata[0] = size;
	inputdata[1] = max;

	//Saves int into array until end of file (EOF)
	int i = 2;
	while(!inFS.eof()) {
		inFS >> inputdata[i++];
	}
	inFS.close();

	return inputdata;
}


/**
 * Starts the error process, calls help to complete info display
 */
void error(void) {
	cout << "\n\nERROR: INVALID FORM";
	help();
}


/**
 * Displays the info necessary to understand how to execute the program successfully
 */
void help(void) {
	cout << "\nThe following flags need to be called with a value:\n-n: File number\n-o: Offset value"
			"\n-s: Scale factor\n-r: Rename files\n\nThe -h: Help\n-S: Get statistics\n-C: Center the signal"
			"\n-N: Normalize the signal\n flags can be called without a value\n\n";
}


/**
 * Takes in an int array and an offset value, offsets each value in the array and prints it to a new file
 */
int offset(int* data, double off, int num) {
	if(data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	ofstream outFS;
	string fname = "Offset_data_";

	if(num<10)
		fname += ("0" + to_string(num) + ".txt");
	else
		fname += (to_string(num) + ".txt");

	outFS.open(fname);

	outFS << data[0] << " "  << setprecision(4) << fixed << off << endl;

	for(int i=2; i<data[0]+2; i++) {
		outFS << static_cast<float>(data[i]+off) << endl;
	}

	outFS.close();
	return 1;
}


/**
 * Takes in an int array and a scale value, scales each value in the array and prints it to a new file
 */
int scale(int* data, double scl, int num) {
	if(data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	ofstream outFS;
	string fname = "Scaled_data_";

	if(num<10)
		fname += ("0" + to_string(num) + ".txt");
	else
		fname += (to_string(num) + ".txt");

	outFS.open(fname);

	outFS << data[0] << " "  << setprecision(4) << fixed << scl << endl;

	for(int i=2; i<data[0]+2; i++) {
		outFS << static_cast<float>(data[i]*scl) << endl;
	}

	outFS.close();
	return 1;
}


/**
 * Prints data from the active int array into a new file of a custom name
 */
int cpfile(int* data, string name) {
	name += ".txt";

	if(data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	ofstream outFS;

	outFS.open(name);

	outFS << data[0] << " "  << data[2] << endl;

	for(int i=2; i<data[0]+2; i++) {
		outFS << (data[i]) << endl;
	}

	outFS.close();

	return 1;
}


/**
 * Takes in an int array and calculates the mean of the data
 */
double mean(int* data) {
	double val = 0;

	for(int i=2; i<data[0]+2; i++) {
		val += data[i];
	}

	val /= data[0];

	return val;
}


/**
 * Takes in an int array and finds the max value of the array
 */
int max(int* data) {
	int val = 0;

	for(int i=2; i<data[0]+2; i++) {
		if(data[i] > val)
			val = data[i];
	}

	return val;
}


/**
 * Takes in an int array, calls mean and max on the array, and prints results to a new file
 */
int getstats(int* data, int num) {
	if(data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	ofstream outFS;

	string fname = "Statistics_data_";

	if(num<10)
		fname += ("0" + to_string(num) + ".txt");
	else
		fname += (to_string(num) + ".txt");

	outFS.open(fname);

	outFS << setprecision(4) << fixed << mean(data);
	outFS.unsetf(ios_base::fixed);
	outFS << " "  << max(data) << endl;

	outFS.close();

	return 1;
}


/**
 * Takes in an int array, offsets each value in the array by the mean and prints it to a new file
 */
int center(int* data, int num) {
	if(data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	ofstream outFS;

	string fname = "Centered_data_";

	if(num<10)
		fname += ("0" + to_string(num) + ".txt");
	else
		fname += (to_string(num) + ".txt");

	outFS.open(fname);

	double off = (-1.0)*mean(data);

	outFS << data[0] << " " << setprecision(4) << fixed << off << endl;

	for(int i=2; i<data[0]+2; i++) {
		outFS << static_cast<float>(data[i]+off) << endl;
	}

	return 1;
}


/**
 * Takes in an int array, scales each value in the array to between 0 and 1 and prints it to a new file
 */
int normalize(int* data, int num) {
	if(data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	ofstream outFS;

	string fname = "Normalized_data_";

	if(num<10)
		fname += ("0" + to_string(num) + ".txt");
	else
		fname += (to_string(num) + ".txt");

	outFS.open(fname);

	double ma = max(data);

	outFS << data[0] << " " << setprecision(4) << fixed << (1/ma) << endl;

	for(int i=2; i<data[0]+2; i++) {
		outFS << static_cast<float>(data[i]/ma) << endl;
	}

	return 1;
}

