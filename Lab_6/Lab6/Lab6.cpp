/*
 * Lab6.cpp
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

	public:
		Signal();
		Signal(int num);
		Signal(string fname);
		~Signal();
		bool operator+(double off);
		bool operator*(double scl);
		int save_file(string name);
		int center();
		int normalize();
		void sig_info();
		int getLength();
		void set(int loc,double val);
		double get(int loc);
		double getMax();
		int getStats();
		double getMin();
		double getMean();
		void copyVector();
		void printVectors();
		void setSize(int size);
};


void error(void);
void help(void);
Signal operator+(Signal &ob1, Signal &ob2);


/**
 * Void constructor. Opens up file #01 by default and saves its data to vector inputdata.
 */
Signal::Signal() {
	cout << "\nOpened file with default constructor\n";
	filenum = 1;
	inputdata = openfile(filenum);
	copyVector();
	getStats();
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
	copyVector();
	getStats();
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
	copyVector();
	getStats();
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
	Signal mySig;

	//For loop will through all parameters to make sure there is nothing wrong
	for(int i=1; i<argc; i++) {
			//Check if a flag
			if(argv[i][0] == '-') {

				//Check if n, for the file number
				if(argv[i][1] == 'n') {
					if((i<argc-1) && (isdigit(argv[i+1][0]))) {
						mySig = Signal(atoi(argv[i+1]));
						i++;
					} else {
						error();
						return 1;
					}
				}

				//Check if f, for the file name
				else if(argv[i][1] == 'f') {
					if((i<argc-1) && (isalpha(argv[i+1][0]))) {
						mySig = Signal(static_cast<string>(argv[i+1]));
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
				mySig = Signal();
			}
	}

	//Menu for choosing operators
	int choice = 1;
	while(choice != 0) {
		cout << "\n1. Perform offset\n2. Perform scale\n3. Center Data\n4. Normalize Data\n5. Show statistics\n6. Save file\n7. Add another data file\n0. Exit\n";
		cout << "\nEnter choice: ";
		cin >> choice;


		switch(choice) {
		case 1: //Offset
			cout << "\nEnter offset value: ";
			int off;
			cin >> off;
			mySig+off;
			cout << "\nOffset completed\n";
			break;

		case 2: //Scale
			cout << "\nEnter scale value: ";
			double scl;
			cin >> scl;
			mySig*scl;
			cout << "\nScale completed\n";
			break;

		case 3: //Center
			mySig.center();
			cout << "\nCenter completed\n";
			break;

		case 4: //Normalize
			mySig.normalize();
			cout << "\nNormalize completed\n";
			break;

		case 5: //Print signal info
			mySig.sig_info();
			break;

		case 6: //Save file
			{cout << "\nEnter desired file name: ";
			string fn;
			cin >> fn;
			mySig.save_file(fn);
			cout << "\nSave file completed\n";
			break;}

		case 7: //Object addition with custom operator
			{cout << "\nEnter file number: ";
			int num;
			cin >> num;
			Signal mySig2 = Signal(num);
			mySig = mySig+mySig2;
			cout << "\nObject addition completed\n";
			break;}
		}
	}

	cout << endl << endl;

	return 0;
}


/****************************************************************************************************************************************/


/**
 * Opens file number from the parameter, reads data into and returns vector
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

	//Saves int into vector until end of file (EOF)
	while(inFS >> in) {
		data.push_back(in);
	}
	inFS.close();

	return data;
}


/**
 * Opens file number from the parameter, reads data into and returns int vector
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

	//Saves int into vector until end of file (EOF)
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
 * Copies the inputdata vector into the moddata vector with a double cast
 */
void Signal::copyVector() {
	moddata.clear();
	for(int i=0; i<length+2; i++) {
		moddata.push_back(static_cast<double>(inputdata[i]));
	}
}


/**
 * Takes in an offset value, offsets each value in the vector
 */
bool Signal::operator+(double off) {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	//make sure to not add onto end of vector if it already exists
	moddata.clear();

	//Keeping with text file formatting of Lab4
	moddata.push_back(length);
	moddata.push_back(off);

	for(int i=2; i<inputdata[0]+2; i++) {
		 moddata.push_back(static_cast<double>(inputdata[i]+off));
	}

	return 1;
}


/**
 * Takes in a scale value, scales each value in the vector
 */
bool Signal::operator*(double scl) {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	//make sure to not add onto end of vector if it already exists
	moddata.clear();

	moddata.push_back(length);
	moddata.push_back(scl);

	for(int i=2; i<inputdata[0]+2; i++) {
		moddata.push_back(static_cast<double>(inputdata[i]*scl));
	}

	return 1;
}


/**
 * Prints data from the active modified vector into a new file of a custom name
 */
int Signal::save_file(string name) {
	name += ".txt";

	//Checks if data has been modified, if not, print the original vector
	if(moddata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
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
 * Calculates the mean of the data, saves it into global average, and returns it
 */
double Signal::getMean() {
	double val = 0;

	for(int i=2; i<moddata[0]+2; i++) {
		val += moddata[i];
	}

	val /= moddata[0];
	average = val;
	return val;
}


/**
 * Finds the min value of the vector, saves it into global mini, and returns it
 */
double Signal::getMin() {
	double val = moddata[1];

	for(int i=2; i<moddata[0]+2; i++) {
		if(moddata[i] < val)
			val = moddata[i];
	}
	mini = val;
	return val;
}


/**
 * Calls mean, min, and max on the vector to refresh stats
 */
int Signal::getStats() {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	getMin();
	getMean();
	getMax();

	return 1;
}


/**
 * Displays current stats info
 */
void Signal::sig_info() {
	getStats();
	cout << endl << "Length of current data set: " << length;
	cout << endl << "Minimum: " << mini;
	cout << endl << "Maximum: " << maxi;
	cout << endl << "Average: " << average << endl;
}


/**
 * Returns current length of moddata
 */
int Signal::getLength() {
	return length;
}


/**
 * Offsets each value in the vector by the mean
 */
int Signal::center() {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	double off = (-1.0)*getMean();

	//Adds offset to the vector, saves to moddata
	(*this)+off;
	getStats();

	return 1;
}


/**
 * Scales each value in the vector to between 0 and 1
 */
int Signal::normalize() {
	if(inputdata.empty()) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	double ma = getMax();

	//Multiplies inputdata by scale, saves to moddata
	(*this)*(1/ma);
	getStats();

	return 1;
}


/**
 * Sets value of signal at specific location, used for object operator
 */
void Signal::set(int loc,double val) {
	moddata[loc+2] = val;
}


/**
 * Gets value at specific location, used for object operator
 */
double Signal::get(int loc) {
	return moddata[loc+2];
}


/**
 * Calculates and returns max value
 */
double Signal::getMax() {
	double val = 0;

	for(int i=2; i<moddata[0]+2; i++) {
		if(moddata[i] > val)
			val = moddata[i];
	}
	maxi = val;
	return maxi;
}


/**
 * For debugging purposes
 */
void Signal::printVectors() {
	cout << endl << endl << "inputdata:" << endl;
	for(int i=0; i<length+2; i++) {
		cout << inputdata[i] << endl;
	}

	cout << endl << endl << "moddata:" << endl;
	for(int i=0; i<length+2; i++) {
		cout << moddata[i] << endl;
	}
}


/**
 * Sets size of vectors, for object operator purposes
 */
void Signal::setSize(int size) {
	inputdata.resize(size+2,0);
	moddata.resize(size+2,0);
	length = size;
}


/**
 * Addition operator, in scope of Lab6.cpp, to add two objects and return new object
 */
Signal operator+(Signal &lhs, Signal &rhs) {
	if(lhs.getLength() != rhs.getLength()) {
		cerr << "\nSignals do not have the same length. Cannot add.\n" ;
		return lhs;
	}

	Signal newSig;

	newSig.set(-2,lhs.getLength());
	newSig.setSize(lhs.getLength());

	if(lhs.getMax() > rhs.getMax()) {
		newSig.set(-1,lhs.getMax());
	} else {
		newSig.set(-1,rhs.getMax());
	}

	for(int i=0; i<newSig.getLength(); i++) {
		newSig.set(i,lhs.get(i)+rhs.get(i));
	}

	newSig.getStats();

	return newSig;
}
