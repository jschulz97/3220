/*
 * Signal.cpp
 *
 * Class for object Signal/main for creating and using such object
 *
 *  Created on: Mar 8, 2018
 *      Author: Jeffrey Schulz
 */

#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

void error(void);
void help(void);

class Signal {
	private:
		int filenum;
		int length;
		int maxi;
		int mini;
		double average;
		vector<int> openfile(int n);
		vector<int> openfile(string fname);
		vector<int> inputdata;
		vector<double> moddata;
		int min();
		double mean();
		int getstats();

	public:
		Signal();
		Signal(int num);
		Signal(string fname);
		~Signal();
		int offset(double off);
		int scale(double scl);
		int save_file(string name);
		int center();
		int normalize();
		void sig_info();
};


/**
 * Void constructor. Opens up file #01 by default and saves its data to vector inputdata.
 */
Signal::Signal() {
	cout << "\nOpened file with default constructor\n";
	filenum = 1;
	inputdata = openfile(filenum);
}


/**
 * Constructor with file num. Opens up that file and saves its data to vector inputdata.
 */
Signal::Signal(int num) {
	if(num < 0) {
		error();
		cout << "\nFile number invalid\n";
	}

	cout << "\nOpened file with file number\n";
	filenum = num;
	inputdata = openfile(num);
}


/**
 * Constructor with file name. Opens up that specific file and saves its data to vector inputdata.
 */
Signal::Signal(string fname) {
	if(fname == "") {
		error();
		cout << "\nFile name empty\n";
	}

	cout << "\nOpened file with file name\n";
	inputdata = openfile(fname);
}


/**
 * Destructor clears up any allocated memory.
 */
Signal::~Signal() {
	//No allocated memory, nothing to destruct
}


/****************************************************************************************************************************************/


/**
 *
 */
int main(int argc, char *argv[]) {

	//Declare new signal object
	Signal mysig;

	//For loop will through all parameters to make sure there is nothing wrong
	for(int i=1; i<argc; i++) {
			//Check if a flag
			if(argv[i][0] == '-') {

				//Check if n, for the file number
				if(argv[i][1] == 'n') {
					if((i<argc-1) && (isdigit(argv[i+1][0]))) {
						mysig = Signal(atoi(argv[i+1]));
						i++;
					} else {
						error();
						return 1;
					}
				}

				//Check if f, for the file name
				else if(argv[i][1] == 'f') {
					if((i<argc-1) && (isalpha(argv[i+1][0]))) {
						mysig = Signal(static_cast<string>(argv[i+1]));
						i++;
					} else {
						error();
						return 1;
					}
				}

				//Something isn't correct if input doesn't match one of these
				else {
					error();
					return 1;
				}
			} else {
				//If no flags, then default constructor
				mysig = Signal();
			}
	}

	//Menu for choosing operators
	int choice = 1;
	while(choice != 0) {
		cout << "\n1. Perform offset\n2. Perform scale\n3. Center Data\n4. Normalize Data\n5. Show statistics\n6. Save file\n0. Exit\n";
		cout << "\nEnter choice: ";
		cin >> choice;

		switch(choice) {
		case 1: //Offset
			cout << "\nEnter offset value: ";
			int off;
			cin >> off;
			mysig.offset(off);
			cout << "\nOffset completed\n";
			break;

		case 2: //Scale
			cout << "\nEnter scale value: ";
			double scl;
			cin >> scl;
			mysig.scale(scl);
			cout << "\nScale completed\n";
			break;

		case 3: //Center
			mysig.center();
			cout << "\nCenter completed\n";
			break;

		case 4: //Normalize
			mysig.normalize();
			cout << "\nNormalize completed\n";
			break;

		case 5: //Print signal info
			mysig.sig_info();
			break;

		case 6: //Save file
			cout << "\nEnter desired file name: ";
			string fn;
			cin >> fn;
			mysig.save_file(fn);
			break;
		}
	}

	cout << endl << endl;
	//delete &mysig;

	return 0;
}


/****************************************************************************************************************************************/


/**
 * Opens file number from the parameter, reads data into and returns int array
 */
vector<int> Signal::openfile(int n) {
	string name;

	//Concatenate strings from input number to open correct data file
	if(n<10)
		name = "Raw_data_0" + to_string(n) + ".txt";
	else
		name = "Raw_data_" + to_string(n) + ".txt";

	//Declare and open file stream
	ifstream inFS;
	inFS.open(name);

	//Check if the file was successfully opened
	if(!inFS.is_open()) {
		cerr << "Could not open the file " << name << endl;
		vector<int> v;
		return v;
	}

	//Grabs first two integers of the file, the num of inputs and the max number
	int size,max,in;
	inFS >> size;
	inFS >> max;

	length = size;
	maxi = max;

	//Create int vector
	vector<int> data;

	data.push_back(size);
	data.push_back(max);

	//Saves int into array until end of file (EOF)
	while(inFS >> in) {
		data.push_back(in);
	}
	inFS.close();

	return data;
}


/**
 * Opens file number from the parameter, reads data into and returns int array
 */
vector<int> Signal::openfile(string fname) {

	//Declare and open file stream
	ifstream inFS;
	inFS.open(fname);

	// check if the file was successfully opened
	if(!inFS.is_open()) {
		cerr << "Could not open the file " << fname << endl;
		vector<int> v;
		return v;
	}

	//Grabs first two integers of the file, the num of inputs and the max number
	int size,max,in;
	inFS >> size;
	inFS >> max;

	length = size;
	maxi = max;

	//Create int vector
	vector<int> data;

	data.push_back(size);
	data.push_back(max);

	//Saves int into array until end of file (EOF)
	while(inFS >> in) {
		data.push_back(in);
	}
	inFS.close();

	return data;
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
	cout << "\nThe following flags need to be called with a value:\n-n: File number\n-f: File name\n\n";
}


/**
 * Takes in an offset value, offsets each value in the array
 */
int Signal::offset(double off) {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	//make sure to not add onto end of array if it already exists
	moddata.clear();

	//Keeping with text file formatting of Lab4
	moddata.push_back(length);
	moddata.push_back(off);

	for(int i=2; i<inputdata[0]+2; i++) {
		 moddata.push_back(static_cast<float>(inputdata[i]+off));
	}

	return 1;
}


/**
 * Takes in a scale value, scales each value in the array
 */
int Signal::scale(double scl) {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	//make sure to not add onto end of array if it already exists
	moddata.clear();

	moddata.push_back(length);
	moddata.push_back(scl);

	for(int i=2; i<inputdata[0]+2; i++) {
		moddata.push_back(static_cast<float>(inputdata[i]*scl));
	}

	return 1;
}


/**
 * Prints data from the active int array into a new file of a custom name
 */
int Signal::save_file(string name) {
	name += ".txt";

	//Checks if data has been modified, if not, print the original vector
	if(moddata.empty()) {
		if(inputdata.empty()) {
			cout << "\nNo data loaded\n";
			return 0;
		}
		else {
			for(auto i:inputdata) {
				moddata.push_back(static_cast<float>(i));
			}
		}
	}

	ofstream outFS;

	outFS.open(name);

	outFS << moddata[0] << " "  << moddata[1] << endl;

	for(int i=2; i<moddata[0]+2; i++) {
		outFS << (moddata[i]) << endl;
	}

	outFS.close();

	return 1;
}


/**
 * Takes in an int array and calculates the mean of the data
 */
double Signal::mean() {
	double val = 0;

	for(int i=2; i<inputdata[0]+2; i++) {
		val += inputdata[i];
	}

	val /= inputdata[0];

	return val;
}


/**
 * finds the min value of the array
 */
int Signal::min() {
	int val = inputdata[1];

	for(int i=2; i<inputdata[0]+2; i++) {
		if(inputdata[i] < val)
			val = inputdata[i];
	}

	return val;
}


/**
 * Takes in an int array, calls mean and max on the array, and prints results to a new file
 */
int Signal::getstats() {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	mini = min();
	average = mean();

	return 1;
}


/**
 * Displays current stats info
 */
void Signal::sig_info() {
	getstats();
	cout << endl << "Length of current data set: " << length;
	cout << endl << "Minimum: " << mini;
	cout << endl << "Maximum: " << maxi;
	cout << endl << "Average: " << average << endl;
}


/**
 * Offsets each value in the vector by the mean
 */
int Signal::center() {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	double off = (-1.0)*mean();

	//make sure to not add onto end of array if it already exists
	moddata.clear();

	moddata.push_back(inputdata[0]);
	moddata.push_back(off);

	for(int i=2; i<inputdata[0]+2; i++) {
		moddata.push_back(static_cast<float>(inputdata[i]+off));
	}

	return 1;
}


/**
 * Scales each value in the array to between 0 and 1
 */
int Signal::normalize() {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	double ma = maxi;

	//make sure to not add onto end of array if it already exists
	moddata.clear();

	moddata.push_back(inputdata[0]);
	moddata.push_back(1.0/ma);

	for(int i=2; i<inputdata[0]+2; i++) {
		moddata.push_back(static_cast<float>(inputdata[i]/ma));
	}

	return 1;
}
