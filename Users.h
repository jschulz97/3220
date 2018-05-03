/**
 *
 */
class BaseUser {
protected:
	int ID = 1;
	string fname;
	string lname;
public:
	virtual BaseUser(string fn, string ln) {fname = fn; lname = ln;};
	virtual int get_permissions() = 0;
	int getID() {return ID;};
}



/****************************************************************************************************/


/**
 *
 */
class Customer : public BaseUser {
public:
	Checkings myCheckings;
	Savings mySavings;
	vector<BaseLoan*> loanVector;

	Customer(string fn, string ln) : BaseUser(fn,ln) {myCheckings = NULL; mySavings = NULL;};
	int get_permissions() {return 1;};
}



/****************************************************************************************************/


/**
 *
 */
class Manager : public BaseUser {
public:
	Manager(string fn, string ln) : BaseUser(fn,ln) {ID = 000000;};
	int get_permissions() {return 2;};
}