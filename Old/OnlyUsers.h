/**
 *
 */
class BaseUser {
protected:
	int ID = 1;
	std::string fname;
	std::string lname;
public:
	BaseUser(std::string fn, std::string ln) {fname = fn; lname = ln;};
	virtual int get_permissions() = 0;
	int getID() {return ID;};
};



/****************************************************************************************************/


/**
 *
 */
class Customer : public BaseUser {
public:
	Checkings myCheckings;
	Savings mySavings;
	std::vector<BaseLoan*> loanVector;

	Customer(std::string fn, std::string ln) : BaseUser(fn,ln) {myCheckings = NULL; mySavings = NULL;};
	int get_permissions() {return 1;};
};



/****************************************************************************************************/


/**
 *
 */
class Manager : public BaseUser {
public:
	Manager(std::string fn, std::string ln) : BaseUser(fn,ln) {ID = 000000;};
	int get_permissions() {return 2;};
};