
class BaseAccount
{
private:
	int act_num;
	int dep;
	char act_name[50];
	char act_type;
public:
	void display_details() const;
	void create_account();
	void edit();
	void report() const;
	void deposit(int);
	void withdraw(int);
	char rettype() const;
	int retact_num() const;
	int retdeposit() const;
	
};


/**
 * Displays account information
 */
void account::display_details() const
{
	cout << endl << "Account Number: " << act_num;
	cout << endl << "Account Username: " << act_name;
	cout << endl << "Type of Account: " << act_type;
	cout << endl << "Balance: " << dep;
}


/**
 * 
 */
void account::create_account()
{
	cout << endl << "Enter Account Number: ";
	cin >> act_num;
	cout << endl << endl << "Enter Name: ";
	cin.ignore();
	cin.getline(act_name,50);
	cout << endl << "What Type of Account do you want to open? (C for Checkings, S for Savings): ";
	cin >> act_type;
	act_type=toupper(act_type);
	cout << endl << "Enter Initial Amount: ";
	cin >> dep;
	cout << endl << "Account Created";
}


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


/**
 * 
 */
void account::deposit(int x)
{
	dep += x;
}


/**
 * 
 */
void account::withdraw(int x)
{
	dep -= x;
}


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