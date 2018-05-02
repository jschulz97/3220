#include<ctime>

/**
 *
 */
class error {
private:
	string msg;
public:
	error(string m) {msg = m;};
	void display() {cerr << endl << msg << endl;};
};


/**
 *
 */
class BaseAccount {
private:
	int act_num;
	double balance;
	string type;
	bool approved;
public:
	virtual BaseAccount() = 0;
	virtual void display_details() const;
	void deposit(double);
	void withdraw(double);
	void edit();
	string get_type() const {return type;};
	int get_act_num() const {return act_num;};
	double get_balance() const {return balance;};
};


/**
 * Displays account information
 */
void BaseAccount::display_details() const
{
	cout << endl << "Account Number: " << act_num;
	cout << endl << "Type of Account: " << act_type;
	cout << endl << "Balance: " << balance;
}


/**
 * 
 */
void BaseAccount::withdraw(double x) {
	try {
		if(x > balance)
			throw error("Attempt to overdraw");
		if(x <= 0) 
			throw error("Not a valid amount to withdraw");
	} catch(error e){
		e.display();
		throw;
	}
	balance -= x;
}


/**
 * 
 */
void BaseAccount::deposit(double x) {
	try {
		if(x <= 0) 
			throw error("Not a valid amount to deposit");
	} catch(error e){
		e.display();
		throw;
	}
	balance += x;
}


/****************************************************************************************************/

/**
 *
 */
class Savings : public BaseAccount {
private:
	double interest_rate;
	int transaction_limit = 5;
	time_t theTime;
	struct tm *aTime;
public:
	Savings();
	Savings(double balance);
	void withdraw(double);
	void desposit(double);
	void display_details() const;
	void calc_limit();
};


/**
 * 
 */
Savings::Savings() {
	balance = 0.0;
	type = "Savings";
	approved = false;
	
	theTime = time(NULL);
	aTime = localtime(&theTime);
}


/**
 * 
 */
Savings::Savings(double x) {
	balance = x;
	type = "Savings";
	approved = false;

	theTime = time(NULL);
	aTime = localtime(&theTime);
}


/**
 * 
 */
void Savings::withdraw(double x) {
	try {
		if(transaction_limit <= 0)
			throw error("Reached Transaction Limit");
		BaseAccount::withdraw(x);
		calc_limit();
	} catch(error e) {
		e.display();
	}
}


/**
 * 
 */
void Savings::deposit(double x) {
	try {
		if(transaction_limit <= 0)
			throw error("Reached Transaction Limit");
		BaseAccount::deposit(x);
		calc_limit();
	} catch(error e) {
		e.display();
	}
}


/**
 *
 */
void Savings::display_details() const : BaseAccount::display_details() {
	cout << endl << "Interest Rate: " << interest_rate << endl;
}


/**
 *
 */
void Savings::calc_limit() {
	//Save previously fetched month, get current time
	int month = aTime->tm_mon;
	theTime = time(NULL);
	aTime = localtime(&theTime);

	//If it's a different month, reset the count
	if(month != aTime->tm_mon)
		transaction_limit = 4;
	else
		transaction_limit--;
	cout << endl << "You have " << transaction_limit << " transactions left this month." << endl;
}

/****************************************************************************************************/

/**
 *
 */
class Checkings : public BaseAccount {
private:
	double interest_rate;
public:
	Savings();
	Savings(double balance);
	void display_details() const;
};




/**
 * 
 */
void account::edit()
{
	cout << endl << "Account Number: " << act_num;
	cout << endl << "Edit Account Username: ";
	cin.ignore();
	cin.getline(act_name,50);
	cout << endl << "Edit Type of Account: ";
	cin >> act_type;
	act_type = toupper(act_type);
	cout << endl << "Edit Balance amount : ";
	cin >> dep;
}


/**
 * 
 */
void account::report() const
{
	cout << act_num << setw(10) << " " << act_name << setw(10) << " " << act_type << setw(6) << dep << endl;
}




/****************************************************************************************************/


/**
 * 
 */
char account::rettype() const
{
	return act_type;
}


/**
 * 
 */
int account::retact_num() const
{
	return act_num;
}


/**
 * 
 */
int account::retdeposit() const
{
	return dep;
}