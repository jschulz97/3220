#include<ctime>
#include<vector>

/**
 *
 */
class error {
private:
	std::string msg;
public:
	error(std::string m) {msg = m;};
	void display() {std::cerr << std::endl << msg << std::endl;};
};


/****************************************************************************************************/


/**
 *
 */
class BaseUser {
protected:
	int ID = 1;
	std::string fname;
	std::string lname;
public:
	BaseUser() {};
	BaseUser(std::string fn, std::string ln, int i) {fname = fn; lname = ln; ID = i;};
	virtual int get_permissions() = 0;
	int getID() {return ID;};
	std::string getFName() {return fname;};
};


/****************************************************************************************************/


/**
 *
 */
class Login {
private:
	int ID;
	std::string enc_pass;
public:
	Login(int i,std::string p) {ID = i; enc_pass = p;};
	int getID() {return ID;};
	std::string getPass() {return enc_pass;};
};


/****************************************************************************************************/



/**
 *
 */
class BaseAccount {
protected:
	int act_num;
	double balance;
	std::string type;
	bool approved = false;
	time_t theTime;
	struct tm *startTime;
public:
	//BaseAccount();
	virtual void display_details() const = 0;
	
	void deposit(double);
	void withdraw(double);
	void edit();
	std::string get_type() const {return type;};
	int get_act_num() const {return act_num;};
	double get_balance() const {return balance;};
	void approve(BaseUser *usr);
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

	std::cout << std::endl << "Account Number: " << act_num;
	std::cout << std::endl << "Type of Account: " << type;
	std::cout << std::endl << "Balance: " << balance;
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
void BaseAccount::approve(BaseUser *usr) {
	try {
		if(usr->get_permissions() < 2)
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
	std::cout << std::endl << "Account Number: " << act_num;
	std::cout << std::endl << "Edit Balance amount : ";
	std::cin >> balance;
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
	void deposit(double);
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
void Savings::display_details() const {
	try {
		if(!approved)
			throw error("Account is not yet approved");
	} catch(error e) {
		e.display();
	}

	std::cout << std::endl << "Account Number: " << act_num;
	std::cout << std::endl << "Type of Account: " << type;
	std::cout << std::endl << "Balance: " << balance;
	std::cout << std::endl << "Interest Rate: " << interest_rate << std::endl;
}


/**
 *
 */
void Savings::calc_limit() {
	//Save previously fetched month, get current time
	int month = startTime->tm_mon;
	//theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	//If it's a different month, reset the count
	if(month != aTime->tm_mon)
		transaction_limit = 4;
	else
		transaction_limit--;
	std::cout << std::endl << "You have " << transaction_limit << " transactions left this month." << std::endl;
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
	void display_details() const;
	void approve_debit_card(BaseUser*);
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
void Checkings::approve_debit_card(BaseUser *usr) {
	try {
		if(usr->get_permissions() < 2)
			throw error("You do not have permission to complete this task");
		card_status = 1;
	} catch(error e) {
		e.display();
		throw;
	}
}


/**
 * 
 */
void Checkings::display_details() const {
	try {
		if(!approved)
			throw error("Account is not yet approved");
	} catch(error e) {
		e.display();
	}

	std::cout << std::endl << "Account Number: " << act_num;
	std::cout << std::endl << "Type of Account: " << type;
	std::cout << std::endl << "Balance: " << balance;
}



/****************************************************************************************************/


/**
 *
 */
class Customer : public BaseUser {
public:
	Checkings myCheckings;
	Savings mySavings;
	//std::vector<BaseLoan*> loanVector;

	Customer() {};
	Customer(std::string fn, std::string ln, int i) : BaseUser(fn,ln,i) {};
	int get_permissions() {return 1;};
};


/**
 *
 */
class Manager : public BaseUser {
public:
	Manager() {};
	Manager(std::string fn, std::string ln) : BaseUser(fn,ln,0) {ID = 100000;};
	int get_permissions() {return 2;};
};

