// L11_Ex1_Inheritance.cpp
// Jeffrey Schulz

#include <iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<cstdlib>
using namespace std;

// --------- BaseSig class and methods ------------------------------
class BaseSig{
	private:
		// neither derived classes nor other users
		// can access private members
	
	protected:	// accessible by derived classes, not by other users.
		int length;
		int *raw_data;	// we could have used a vector
		int openfile();
		int openfile(int L);
		
	public:
		BaseSig();		// default constructor.
		BaseSig(int L);	// parametric constructor
		virtual ~BaseSig();		// virtual destructor
		int getLength() { return length; };
		int getRawValue(int pos);
		static int numObjects;	// static, only one member for the entire hierarchy
		virtual void printInfo();	// virtual function
};

int BaseSig::numObjects = 0;	// initialize static data member

/**
 * Base class constructor
 */
BaseSig::BaseSig(){
	length = 0;
	raw_data = NULL;
	if(openfile())
		numObjects++;
	else
		exit(0);
}


/**
 * Base class parametric constructor
 */
BaseSig::BaseSig(int L){
	length = L;
	raw_data = new int[L+2];
	if(raw_data == NULL)
		cerr << "Error in memory allocation";
	if(openfile(L))
		numObjects++;
	else
		exit(0);
}


/**
 * Base class destructor
 */
BaseSig::~BaseSig(){
	if(raw_data)
		delete raw_data;
	cout << "Goodbye, BaseSig." << endl;
}


/**
 * Opens file, puts data into raw_data array
 */
int BaseSig::openfile() {

	string name = "Raw_data_03.txt";

	//Declare and open file stream
	ifstream inFS;
	inFS.open(name);

	//Check if the file was successfully opened
	if(!inFS.is_open()) {
		cerr << "Could not open the file " << name << endl;
		return 0;
	}

	//Grabs first two integers of the file, the num of inputs and the max number
	inFS >> length;
	int max;
	inFS >> max;

	raw_data = new int[length+2];
	raw_data[0] = length;
	raw_data[1] = max;

	//Saves int into array until end of file (EOF)
	for(int i = 2; i < length+2; i++) {
		inFS >> raw_data[i];
	}
	inFS.close();

	return 1;
}


/**
 * Opens file,
 */
int BaseSig::openfile(int L) {

	string name = "Raw_data_03.txt";

	//Declare and open file stream
	ifstream inFS;
	inFS.open(name);

	//Check if the file was successfully opened
	if(!inFS.is_open()) {
		cerr << "Could not open the file " << name << endl;
		return 0;
	}

	//Grabs first two integers of the file, the num of inputs and the max number
	int max,len;
	inFS >> len;
	inFS >> max;

	if(L>len) {
		L = len;
		length = len;
	}

	raw_data[0] = L;
	raw_data[1] = max;

	//Saves int into array until end of file (EOF)
	for(int i = 2; i < L+2; i++) {
		inFS >> raw_data[i];
	}
	inFS.close();

	return 1;
}


/**
 * Gets value at certain position of raw_data array
 */
int BaseSig::getRawValue(int pos) {
	if(pos < 0)			// invalid index
		return(raw_data[2]);
	else if(pos >= length+2)	// invalid index
		return(raw_data[length+1]);
	else
		return(raw_data[pos+2]);
}


/**
 * Prints stats of base signal
 */
void BaseSig::printInfo() {
	cout << "\nLength: " << length << endl;
}
// -----------------------------------------------------------------------------------------------------------


// --------- ExtendSig class and methods ----------------------------
class ExtendSig : public BaseSig{ // ExtendSig is derived from class BaseSig
	private: 
		double average;		// add new data members
		double *data;		// we could have used a vector
		
	public:
		ExtendSig(int L);	//derived classes need a new constructor
		~ExtendSig();
		double getValue(int pos);
		int setValue(int pos, double val);
		double getAverage();
		void printInfo();
};


/**
 * Constructor for Extended Signal, contructs with base class constructor first
 */
ExtendSig::ExtendSig(int L) : BaseSig(L) {
	data = new double[L];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 2; i < L+2; i++)
			data[i-2] = (double)raw_data[i];
		average = getAverage();
	}
}


/**
 * Destructor for extended signal
 */
ExtendSig::~ExtendSig() {
	delete data;
	cout << "Goodbye, ExtendSig." << endl;
}


/**
 * Gets the value of the signal at a certain position
 */
double ExtendSig::getValue(int pos) {
	if(pos < 0)			// invalid index
		return(data[0]);
	else if(pos >= length)	// invalid index
		return(data[length-1]);	
	else
		return(data[pos]);
}


/**
 * Sets the value of the signal at a ceratin position
 */
int ExtendSig::setValue(int pos, double val) {
	if((pos < 0) || (pos >= length))
		return(-1);	// invalid index
	else {
		data[pos] = val;
		average = getAverage();
		return(0);	// success
	}
}


/**
 * Gets average of extended signal
 */
double ExtendSig::getAverage() {
	if(length == 0)
		return(0.0);
	else {
		double temp = 0.0;
		for(int i = 0; i < length; i++)
			temp += data[i];
		return(temp/(double)length);
	}
}


/**
 * Prints stats for extended signal
 */
void ExtendSig::printInfo() {
	cout << "\nLength: " << length << endl
		 << "Average: " << average << endl;
}
// -----------------------------------------------------------------------------------------------------------



// --------- ProcessedSig class and methods ----------------------------
class ProcessedSig : public BaseSig{ // ExtendSig is derived from class BaseSig
	private:
		double average;		// add new data members
		double *data;		// we could have used a vector
		double max;
		double min;
		int openfile(int L);

	public:
		ProcessedSig(int L);	//derived classes need a new constructor
		~ProcessedSig();
		double getValue(int pos);
		int setValue(int pos, double val);
		double getAverage();
		double getMax();
		int normalize();
		void printInfo();
};


/**
 * Constructor for processed signal. interprets raw_data from the base class constructor
 */
ProcessedSig::ProcessedSig(int L) : BaseSig(L) {
	data = new double[L];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 2; i < L+2; i++)
			data[i-2] = (double)raw_data[i];
		average = getAverage();
		max = raw_data[1];
		min = 0;
	}
}


/**
 * Destructor for data array in processed sig
 */
ProcessedSig::~ProcessedSig() {
	delete data;
	cout << "Goodbye, ProcessedSig." << endl;
}


/**
 * Gets the value of the signal at a certain position
 */
double ProcessedSig::getValue(int pos) {
	if(pos < 0)			// invalid index
		return(data[0]);
	else if(pos >= length)	// invalid index
		return(data[length-1]);
	else
		return(data[pos]);
}


/**
 * Sets the value of the array at a certain position
 */
int ProcessedSig::setValue(int pos, double val) {
	if((pos < 0) || (pos >= length))
		return(-1);	// invalid index
	else {
		data[pos] = val;
		average = getAverage();
		return(0);	// success
	}
}


/**
 * Gets average of processed data
 */
double ProcessedSig::getAverage() {
	if(length == 0)
		return(0.0);
	else {
		double temp = 0.0;
		for(int i = 0; i < length; i++)
			temp += data[i];
		return(temp/(double)length);
	}
}

/**
 * Prints out stats for this signal
 */
void ProcessedSig::printInfo() {
	cout << "\nLength: " << length << endl
		 << "Average: " << average << endl
		 << "Maximum: " << max << endl
		 << "Minimum: " << min << endl;
}


/**
 * Gets max value
 */
double ProcessedSig::getMax() {
	return max;
}


/**
 * Normalizes signal and returns 1 if successful
 */
int ProcessedSig::normalize(){
	if(raw_data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	for(int i=2; i<length+2; i++) {
		data[i-2] = static_cast<float>(raw_data[i]/max);
	}

	max = 1;
	average = getAverage();

	return 1;
}


// --------- ProcessedSig_v2 class and methods ----------------------------
class ProcessedSig_v2 : public ExtendSig { // Derived from ExtendSig
	private:
		double average;		// add new data members
		double *data;		// we could have used a vector
		double max;
		double min;

	public:
		ProcessedSig_v2(int L);	//derived classes need a new constructor
		~ProcessedSig_v2();
		double getValue(int pos);
		int setValue(int pos, double val);
		double getAverage();
		double getMax();
		int normalize();
		void printInfo();
};


/**
 * Constructor for processed signal v2. Constructs with Extended Signal first
 */
ProcessedSig_v2::ProcessedSig_v2(int L) : ExtendSig(L) {
	data = new double[L];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 2; i < L+2; i++)
			data[i-2] = (double)raw_data[i];
		average = getAverage();
		max = raw_data[1];
		min = 0;
	}
}


/**
 * Destructor for Processed signal v2
 */
ProcessedSig_v2::~ProcessedSig_v2() {
	delete data;
	cout << "Goodbye, ProcessedSig." << endl;
}


/**
 * Gets value of signal at a certain position
 */
double ProcessedSig_v2::getValue(int pos) {
	if(pos < 0)			// invalid index
		return(data[0]);
	else if(pos >= length)	// invalid index
		return(data[length-1]);
	else
		return(data[pos]);
}


/**
 * Sets the value of the signal at a certain position
 */
int ProcessedSig_v2::setValue(int pos, double val) {
	if((pos < 0) || (pos >= length))
		return(-1);	// invalid index
	else {
		data[pos] = val;
		average = getAverage();
		return(0);	// success
	}
}


/**
 * Calculates and returns the average of the signal
 */
double ProcessedSig_v2::getAverage() {
	if(length == 0)
		return(0.0);
	else {
		double temp = 0.0;
		for(int i = 0; i < length; i++) {
			temp += data[i];
		}
		return(temp/(double)length);
	}
}


/**
 * Prints stats for the signal
 */
void ProcessedSig_v2::printInfo() {
	cout << "\nLength: " << length << endl
		 << "Average: " << average << endl
		 << "Maximum: " << max << endl
		 << "Minimum: " << min << endl;
}


/**
 * Gets max value
 */
double ProcessedSig_v2::getMax() {
	return max;
}


/**
 * Normalizes signal. Returns 1 if successful
 */
int ProcessedSig_v2::normalize(){
	if(raw_data == NULL) {
		cout << "\nNo data loaded\n";
		return 0;
	}

	for(int i=0; i<length; i++) {
		data[i] = static_cast<float>(data[i]/max);
	}

	max = 1;
	average = getAverage();

	return 1;
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------


// Main function. A few examples
int main()
{
	//Construct new BaseSig and ExtendSig objects
	BaseSig bsig1(5);
	ExtendSig esig1(10);

	//Static value of numObjects should be incremented every time an object is created anywhere within these 4 object types
	cout << "# of objects created: " << bsig1.numObjects << endl
		 << "# of objects created: " << esig1.numObjects << endl;
	bsig1.printInfo();
	esig1.printInfo();
	cout << "--------------------------------------------" << endl;
	
	cout << endl << bsig1.getRawValue(3) << endl
		 << esig1.getRawValue(7) << endl
		 << esig1.getValue(7) << endl;
	cout << "--------------------------------------------" << endl;
	
	cout << endl << esig1.setValue(7, 2.5) << endl
		 << esig1.setValue(12, 2.0) << endl;
		 
	cout << endl << esig1.getValue(7) << endl;
	esig1.printInfo();
	cout << "--------------------------------------------" << endl;
	
	BaseSig *ptrB = &bsig1;	// pointer points to object of base class
	BaseSig &refB = bsig1;  // reference to object of base class
	ptrB->printInfo();		// which version is used?
	refB.printInfo();		// which version is used?
	cout << "--------------------------------------------" << endl;
	
	ptrB = &esig1;	// pointer points to the base part of the object of derived class
	BaseSig &refB2 = esig1; // reference bound to the base part of esig1
	ptrB->printInfo();		// which version is used?
	refB2.printInfo();		// which version is used?
	cout << "--------------------------------------------" << endl;

	ExtendSig esig2(5);
	ProcessedSig psig1(10);

	cout << "# of objects created: " << esig2.numObjects << endl << endl;

	cout << "Value at pos 4: " << psig1.getValue(4) << endl;
	cout << "Average of ProcessedSig: " << psig1.getAverage() << endl;

	psig1.setValue(4,8);
	cout << "Value at pos 4: " << psig1.getValue(4) << endl;
	cout << "Average of ProcessedSig: " << psig1.getAverage() << endl;

	psig1.setValue(5,0);
	cout << "Value at pos 5: " << psig1.getValue(5) << endl;
	psig1.printInfo();

	psig1.normalize();
	cout << "\nNormalized Signal:\n";
	psig1.printInfo();
	cout << "Value at pos 5: " << psig1.getValue(5) << endl;
	cout << "--------------------------------------------" << endl;

	ProcessedSig_v2 psig2(55);
	cout << "\nProcessedSig_v2 psig2(55) has length: " << psig2.getLength() << "\nBecause the raw_data is only " << psig2.getLength() << " elements long." << endl;
	cout << "\nProcessedSig_v2 info:";
	psig2.printInfo();

	cout << "\nNormalized Signal:\n";
	psig2.normalize();
	psig2.printInfo();

	cout << "\npsig2.getValue(0): ";
	cout << psig2.getValue(0) << endl;
	cout << "psig2.setValue(0,8)\npsig2.getValue(0): ";
	psig2.setValue(0,8);
	cout << psig2.getValue(0) << endl;

	cout << endl << endl;
	return 0;
}
