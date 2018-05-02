/**
 *
 */
class BaseUser {
protected:
	int ID;
public:
	virtual int get_permissions() = 0;
}



/****************************************************************************************************/


/**
 *
 */
class Customer : public BaseUser {
public:
	int get_permissions() {return 1;};
}



/****************************************************************************************************/


/**
 *
 */
class Manager : public BaseUser {
public:
	int get_permissions() {return 2;};
}