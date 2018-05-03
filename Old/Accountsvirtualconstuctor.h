#include<ctime>
//#include "Users.h"
using namespace std;

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
protected:
	int act_num;
	double balance;
	string type;
	bool approved = false;
	time_t theTime;
	struct tm *startTime;
public:
	BaseAccount() = 0;
	virtual void display_details() const;
	
	void deposit(double);
	void withdraw(double);
	void edit();
	string get_type() const {return type;};
	int get_act_num() const {return act_num;};
	double get_balance() const {return balance;};
	//void approve(*BaseUser);
};


/**
 * Displays account information
 */
void BaseAccount::display_details() const
{
	try {
		if(!approved)
			throw error("Account is not yet approved");
	} catch(error e) {
		e.display();
	}

	cout << endl << "Account Number: " << act_num;
	cout << endl << "Type of Account: " << act_type;
	cout << endl << "Balance: " << balance;
}


/**
 * 
 */
void BaseAccount::withdraw(double x) {
	try {
		if(!approved)
			throw error("Account is not yet approved");
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
		if(!approved)
			throw error("Account is not yet approved");
		if(x <= 0) 
			throw error("Not a valid amount to deposit");
	} catch(error e){
		e.display();
		throw;
	}
	balance += x;
}


/**
 * 
 */
void BaseAccount::approve(BaseUser* usr) {
	try {
		if(usr.get_permissions() < 2)
			throw error("You do not have permission to complete this task");
		approved = true;
	} catch(error e) {
		e.display();
		throw;
	}
}


/**
 * 
 */
void BaseAccount::edit()
{
	cout << endl << "Account Number: " << act_num;
	cout << endl << "Edit Balance amount : ";
	cin >> balance;
}


/****************************************************************************************************/

/**
 *
 */
class Savings : public BaseAccount {
private:
	double interest_rate;
	int transaction_limit = 5;
	void calc_limit();
public:
	Savings();
	Savings(double);
	void withdraw(double);
	void desposit(double);
	void display_details() const;
};


/**
 * 
 */
Savings::Savings() : BaseAccount() {
	balance = 0.0;
	type = "Savings";
	approved = false;
	
	theTime = time(NULL);
	startTime = localtime(&theTime);
}


/**
 * 
 */
Savings::Savings(double x) : BaseAccount() {
	balance = x;
	type = "Savings";
	approved = false;

	theTime = time(NULL);
	startTime = localtime(&theTime);
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
	//theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

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
	int card_status = 0;
public:
	Checkings();
	Checkings(double);
	void request_debit_card();
};


/**
 * 
 */
Checkings::Checkings() : BaseAccount() {
	balance = 0;
	type = "Checkings";
	approved = false;

	theTime = time(NULL);
	startTime = localtime(&theTime);
}


/**
 * 
 */
Checkings::Checkings(double x) : BaseAccount() {
	balance = x;
	type = "Checkings";
	approved = false;

	theTime = time(NULL);
	startTime = localtime(&theTime);
}


/**
 * 
 */
void Checkings::request_debit_card() {
	try {
		if(!approved)
			throw error("Account is not yet approved");
		card_status = -1; //Card status -1 means card is waiting on approval
	} catch(error e) {
		e.display();
	}
}


/**
 * 
 */
void Checkings::approve_debit_card(BaseUser* usr) {
	try {
		if(usr.getPermission() < 2)
			throw error("You do not have permission to complete this task");
		card_status = 1;
	} catch(error e) {
		e.display();
		throw;
	}


}



/****************************************************************************************************/