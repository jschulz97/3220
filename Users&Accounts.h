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
	std::string getLName() {return lname;};
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
	Login() {};
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
public:
	//BaseAccount();
	virtual void display_details() const = 0;
	bool approved = false;
	
	int deposit(double);
	int withdraw(double);
	void edit();
	std::string get_type() const {return type;};
	int get_act_num() const {return act_num;};
	double get_balance() const {return balance;};
	void approve(BaseUser *usr);
};


/**
 * 
 */
int BaseAccount::withdraw(double x) {
	try {
		if(!approved)
			throw error("Account is not yet approved");
		if(x > balance)
			throw error("Attempt to overdraw");
		if(x <= 0) 
			throw error("Not a valid amount to withdraw");
	} catch(error e){
		e.display();
		return 0;
	}
	balance -= x;
	return 1;
}


/**
 * 
 */
int BaseAccount::deposit(double x) {
	try {
		if(!approved)
			throw error("Account is not yet approved");
		if(x <= 0) 
			throw error("Not a valid amount to deposit");
	} catch(error e){
		e.display();
		return 0;
	}
	balance += x;
	return 1;
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
	int transactions_left = 5;
	void calc_limit();
	int mon;
public:
	Savings();
	Savings(int,double,bool,int,double,int);
	int get_mon() {return mon ;};
	int get_trans() {return transactions_left;};
	double get_int_rate() {return interest_rate;};
	int withdraw(double);
	int deposit(double);
	void display_details() const;
};

/**
 * 
 */
Savings::Savings() : BaseAccount() {
	balance = 0.0;
	type = "Savings";
	approved = false;

	time_t theTime = time(NULL);
	struct tm *startTime = localtime(&theTime);
	mon = startTime->tm_mon;
}


/**
 * 
 */
Savings::Savings(int act,double x,bool app,int m,double inter,int tr) : BaseAccount() {
	act_num = act;
	balance = x;
	type = "Savings";
	approved = app;
	mon = m;
	interest_rate = inter;
	transactions_left = tr;
}


/**
 * 
 */
int Savings::withdraw(double x) {
	try {
		if(transactions_left <= 0)
			throw error("Reached Transaction Limit");
		int ret = BaseAccount::withdraw(x);
		calc_limit();
		return ret;
	} catch(error e) {
		e.display();
		return 0;
	}
}


/**
 * 
 */
int Savings::deposit(double x) {
	try {
		if(transactions_left <= 0)
			throw error("Reached Transaction Limit");
		int ret = BaseAccount::deposit(x);
		calc_limit();
		return ret;
	} catch(error e) {
		e.display();
		return 0;
	}
}


/**
 *
 */
void Savings::display_details() const {
	try {
		if(!approved)
			throw error("Savings account is not yet approved for this user");
	} catch(error e) {
		e.display();
	}

	std::cout << std::endl << "Type of Account: " << type;
	std::cout << std::endl << "Account Number: " << act_num;	
	std::cout << std::endl << "Balance: " << balance;
	std::cout << std::endl << "Interest Rate: " << interest_rate;
	std::cout << std::endl << "Transactions left this month: " << transactions_left << std::endl;
}


/**
 *
 */
void Savings::calc_limit() {
	//Save previously fetched month, get current time
	int month = mon;

	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	//If it's a different month, reset the count
	if(month != aTime->tm_mon)
		transactions_left = 4;
	else
		transactions_left--;
	std::cout << std::endl << "You have " << transactions_left << " transactions left this month." << std::endl;
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
	Checkings(int,double,bool,int);
	int get_card_status() {return card_status;};
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
}


/**
 * 
 */
Checkings::Checkings(int act,double x,bool app,int card) : BaseAccount() {
	act_num = act;
	balance = x;
	type = "Checkings";
	approved = app;
	card_status = card;
}


/**
 * 
 */
void Checkings::request_debit_card() {
	try {
		if(!approved)
			throw error("Checkings account is not yet approved for this user");
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
			throw error("Checkings account is not yet approved for this user");
	} catch(error e) {
		e.display();
	}

	std::cout << std::endl << "Type of Account: " << type;
	std::cout << std::endl << "Account Number: " << act_num;	
	std::cout << std::endl << "Balance: " << balance;
	std::cout << std::endl << "Debit card status: " << card_status;
}



/****************************************************************************************************/

/**
 * Customer, a type of BaseUser
 */
class Customer : public BaseUser {
public:
	Checkings* myCheckings = NULL;
	Savings* mySavings = NULL;
	//std::vector<BaseLoan*> loanVector;

	Customer() {};
	Customer(std::string fn, std::string ln, int i) : BaseUser(fn,ln,i) {};
	int get_permissions() {return 1;};
	void edit_account();
	void add_account();
	void deposit();
	void withdraw();
	void display_account_details();
};


/**
 * Displays all bank account details
 */
void Customer::display_account_details() {
	if(mySavings != NULL)
		mySavings->display_details();
	if(myCheckings != NULL)
		myCheckings->display_details();
}


/**
 * Handles deposit with dynamic menu
 */
void Customer::deposit() {
	bool swap = false;
	bool two = false;
	int choice = 1;
	while(choice != 0) {
		system("cls");
		std::cout << std::endl << "\tChoose an account to deposit to: ";
		std::cout << std::endl << std::endl << "0) Exit to main menu";
		if(mySavings != NULL && myCheckings == NULL) {
			std::cout << std::endl << std::endl << "1) Savings";
		} else if(mySavings == NULL && myCheckings != NULL) {
			swap = true;
			std::cout << std::endl << std::endl << "1) Checkings";
		} else if(mySavings == NULL && myCheckings == NULL) {
			std::cout << "\n\nNo accounts exist";
		} else {
			two = true;
			std::cout << std::endl << std::endl << "1) Savings";
			std::cout << std::endl << std::endl << "2) Checkings";
		}
		std::cout << std::endl << std::endl << "Make Your Choice: ";
		std::cin >> choice;
		system("cls");

		if(swap && choice == 1) { //Correct for menu dynamics
			choice = 2;
		}

		switch(choice)
		{
		case 1: //Savings
			double amt;
			do{ //Loop until deposit succeeds
				std::cout << "\nEnter Amount: ";
				std::cin >> amt;
			} while(!(mySavings->deposit(amt)));
			std::cout << "\n\tSuccessfully deposited.";
			break;
		case 2: //Checkings
			if(two) {
				double amt;
				do{ //Loop until deposit succeeds
					std::cout << "\nEnter Amount: ";
					std::cin >> amt;
				} while(!(myCheckings->deposit(amt)));
				std::cout << "\n\tSuccessfully deposited.";
			} else {
				std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			}
			break;
		case 0:
			std::cout << "\n\nLeaving deposit";
			break;
		default:
			std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			break;
		}
	}

}


/**
 * Handles withdrawal with dynamic menu
 */
 void Customer::withdraw() {
 	bool swap = false;
	bool two = false;
	int choice = 1;
	while(choice != 0) {
		system("cls");
		std::cout << std::endl << "\tChoose an account to withdraw from: ";
		std::cout << std::endl << std::endl << "0) Exit to main menu";
		if(mySavings != NULL && myCheckings == NULL) {
			std::cout << std::endl << std::endl << "1) Savings";
		} else if(mySavings == NULL && myCheckings != NULL) {
			swap = true;
			std::cout << std::endl << std::endl << "1) Checkings";
		} else if(mySavings == NULL && myCheckings == NULL) {
			std::cout << "\n\nNo accounts exist";
		} else {
			two = true;
			std::cout << std::endl << std::endl << "1) Savings";
			std::cout << std::endl << std::endl << "2) Checkings";
		}
		std::cout << std::endl << std::endl << "Make Your Choice: ";
		std::cin >> choice;
		system("cls");

		if(swap && choice == 1) { //Correct for menu dynamics
			choice = 2;
		}

		switch(choice)
		{
		case 1: //Savings
		double amt;
			do{ //Loop until withdrawal succeeds
				std::cout << "\nEnter Amount: ";
				std::cin >> amt;
			} while(!(mySavings->withdraw(amt)));
			std::cout << "\n\tSuccessfully withdrew.";
			break;
		case 2: //Checkings
			if(two) {
				double amt;
				do{ //Loop until withdrawal succeeds
					std::cout << "\nEnter Amount: ";
					std::cin >> amt;
				} while(!(myCheckings->withdraw(amt)));
				std::cout << "\n\tSuccessfully withdrew.";
			} else {
				std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			}
			break;
		case 0:
			std::cout << "\n\nLeaving withdraw";
			break;
		default:
			std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			break;
		}
	}
 }


/**
 * Edits account details, including name and savings/checkings accounts
 */
void Customer::edit_account() {
	bool swap = false;
	bool three = false;
	int choice = 1;
	while(choice != 0) {
		system("cls");
		std::cout << std::endl << "\tEditing user account details for user #" << ID;
		std::cout << std::endl << std::endl << "0) Exit to main menu";
		std::cout << std::endl << std::endl << "1) Edit name";
		if(mySavings != NULL && myCheckings == NULL) {
			std::cout << std::endl << std::endl << "2) Delete Savings";
		} else if(mySavings == NULL && myCheckings != NULL) {
			swap = true;
			std::cout << std::endl << std::endl << "2) Delete Checkings";
		} else if(mySavings == NULL && myCheckings == NULL) {
			std::cout << "\n\nNo accounts exist";
		} else {
			three = true;
			std::cout << std::endl << std::endl << "2) Delete Savings";
			std::cout << std::endl << std::endl << "3) Delete Checkings";
		}
		std::cout << std::endl << std::endl << "Make Your Choice: ";
		std::cin >> choice;
		system("cls");

		if(swap && choice == 2) { //Correct for menu dynamics
			choice = 3;
		}

		switch(choice)
		{
		case 1: //Edit name
			std::cout << "\nNew first name: ";
			std::cin >> fname;
			std::cout << "\nNew last name: ";
			std::cin >> lname;
			break;
		case 2: //Delete Savings
			mySavings = NULL;
			std::cout << "\n\tSavings account deleted";
			break;
		case 3: //Delete Checkings
			if(three) {
				myCheckings = NULL;
				std::cout << "\n\tCheckings account deleted";
			} else {
				std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			}
			break;
		case 0:
			std::cout << "\n\nLeaving account edit";
			break;
		default:
			std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			break;
		}
	}
}


/**
 * Adds bank account to user with dynamic menu
 */
void Customer::add_account() {
	bool swap = false;
	bool two = false;
	int choice = 1;
	while(choice != 0) {
		system("cls");
		std::cout << std::endl << "\tAdd bank account for user #" << ID;
		std::cout << std::endl << std::endl << "0) Exit to main menu";
		if(mySavings == NULL && myCheckings != NULL) {
			std::cout << std::endl << std::endl << "1) Add Savings";
		} else if(mySavings != NULL && myCheckings == NULL) {
			swap = true;
			std::cout << std::endl << std::endl << "1) Add Checkings";
		} else if(mySavings != NULL && myCheckings != NULL) {
			std::cout << "\n\nAlready contains both types of accounts";
		} else {
			two = true;
			std::cout << std::endl << std::endl << "1) Add Savings";
			std::cout << std::endl << std::endl << "2) Add Checkings";
		}
		std::cout << std::endl << std::endl << "Make Your Choice: ";
		std::cin >> choice;
		system("cls");

		if(swap && choice == 1) { //Correct for menu dynamics
			choice = 2;
		}

		switch(choice)
		{
		case 1: //Add Savings
			mySavings = new Savings();
			std::cout << "\n\tSavings account created, waiting on approval of bank manager.";
			break;
		case 2: //Add Checkings
			if(two) {
				myCheckings = new Checkings();
				std::cout << "\n\tCheckings account created, waiting on approval of bank manager.";
			} else {
				std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			}
			break;
		case 0:
			std::cout << "\n\nLeaving account add";
			break;
		default:
			std::cerr << std::endl << std::endl << "Incorrect Input" << std::endl;
			break; 
		}
	}
}


/**
 * Manager, a type of BaseUser. Contains no accounts but has admin access
 */
class Manager : public BaseUser {
public:
	Manager() {};
	Manager(std::string fn, std::string ln) : BaseUser(fn,ln,0) {ID = 100000;};
	int get_permissions() {return 2;};
};
