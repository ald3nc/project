#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

// Maximum amounts constants
#define MAX_NAME_LENGTH 20
#define MAX_PASS_LENGTH 20
#define MAX_AMOUNT_DEPOSIT_WITHDRAW 2147483647	// Max range for a floating-point value
#define MAX_AMOUNT_ACCOUNT 2147483647			// Max range for a floating-point value

// Program control constants 
#define RESTART "***RESTART***"
#define EXIT "***EXIT***"

// Data file access control constants
#define DATA_CUSTOMER "customers.txt"
#define DATA_CHECKING "checking.txt"
#define DATA_SAVINGS "savings.txt"
#define DATA_EMPLOYEE "employees.txt"
#define DATA_PAYROLL "payroll.txt"
#define DATA_MANAGER "managers.txt"

/* STRUCTURE: prompts
 * DESCRIPTION: Stores all of the prompts to be displayed to the user
 */
struct prompts {
	// Menu prompts
	string menu_main = "Enter 1 to Log in as a Customer\nEnter 2 to log in as an Employee\nEnter 3 to Log in as a Manager\nEnter 4 to Request New Customer Account\nEnter 5 to Exit";
	string menu_account = "Enter 1 to Add Funds\nEnter 2 to Withdraw Funds\nEnter 3 to Return to Exit Menu";
	string menu_customer = "Enter 1 to Manage Checking Account\nEnter 2 to Manage Savings Account\nEnter 3 to Exit Menu";
	string menu_employee = "Enter 1 to Manage a Customer Account\nEnter 2 to View Payroll Information\nEnter 3 to Add Customer Account\nEnter 4 to Remove Customer Account\nEnter 5 to View All Customer Accounts\nEnter 6 to Exit Menu";
	string menu_manager = "Enter 1 to Manage Customers\nEnter 2 to Manage Employees\nEnter 3 to Exit Menu";	
	string menu_manage_customer = "Enter 1 to Add Funds to Savings\nEnter 2 to Add Funds to Checking\nEnter 3 to Withdraw From Savings\nEnter 4 to Withdraw from Checking";
	string menu_customer_account_name = "Which Customer Account Would you Like to Manage?\n(Enter 'exit' to Exit Menu)";
	string menu_addRemove = "Enter 1 to Add Funds to Savings\nEnter 2 to Add Funds to Checking\nEnter 3 to Withdraw from Savings\nEnter 4 to Withdraw from Checking\nEnter 5 to Exit";
	string menu_manageEmployees = "Enter 1 to Change an Employee's Pay\nEnter 2 to Add an Employee\nEnter 3 to Remove an Employee\nEnter 4 to View All Employees\nEnter 5 to Exit Menu";
	string menu_manageCustomers = "Enter 1 to Manage a Customer Account\nEnter 2 to Add a New Customer\nEnter 3 to Remove a Customer\nEnter 4 to View all Accounts";

	// Login messages
	string username = "Enter Your Username (Enter 'exit' to return to previous menu): ";
	string password = "Enter Your Password: ";
	string deposit = "Enter Amount You Would Like to Deposit";
	string withdraw = "Enter Amount You Would Like to Withdraw";

	// Information messages
	string info_balance = "Your Balance is: \n$";
	string info_hourly_rate = "Your Hourly Rate is: \n$";

	// Error handling messages (Soft Errors)
	string soft_input = "Invalid Input";
	string soft_customer_name = "There is Already a Customer with that Name";
	string soft_invalid_customer = "Not a Valid Customer";
	string try_again = "Would you like to try again? (yes) -or- (no): ";
	string try_again_please = "Please Try Again";
	string exit = "Enter 'exit' to Exit Current Menu";

	// New customer data acquisition
	string new_customer_name = "Enter Name of New Customer: ";
	string new_customer_password = "Enter Password of New Customer: ";
	string new_customer_checking = "Enter Checking Balance for New Customer: ";
	string new_customer_savings = "Enter Savings Balance for New Customer: ";

	// Customer Options
	string customer_name = "Enter Name of Customer (Enter 'exit' to return to previous menu): ";

	// Manager Options
	string manager_customer = "Enter Name of Customer Account you would like to Manage (Enter 'exit' to return to previous menu): ";
	string manager_employee = "Enter Name of Employee you would like to Manage (Enter 'exit' to return to previous menu): ";

	// Error messages
	string error_general = "ERROR: General Error";
	string error_fileAccess = "ERROR: Unable to open file";
	string error_input = "ERROR: Invalid Input";
	string error_characterOverflow = "ERROR: Too many characters";
}prompt;

/* CLASS: Input
 * DESCRIPTION: Used to obtain valid input from the user.
 */
class Input {
	private:
	public:
		Input() {};
		~Input() {};
		string get_string(int maxLength);
		string get_string(int maxLength, string prompt);
		int get_integer(int min, int max);
		int get_integer(int min, int max, string prompt);
		float get_float(float min, float max);
		float get_float(float min, float max, string prompt);
}userInput; // END CLASS Input

/* CLASS: Input
 * METHOD: getString
 * DESCRIPTION: Gets valid string from user with a number of characters less than <maxLength>.
 *				If error has occurred:
 *					Returns "false" to repeat process/prompt which called this method.
 *					Returns "exit" to end process/prompt which called this method.
 */
string Input::get_string(int maxLength) {
	string raw;
	cout << "\n--> ";

	try {
		getline(cin,raw);
		if( raw.size() > maxLength )
			throw length_error( prompt.error_characterOverflow );
		if( raw == "exit" )
			return EXIT;
	} catch (length_error x) {
		string cont;

		cout << endl << x.what();
		cout << endl << prompt.try_again;

		cont = get_string(maxLength);

		if( cont == "yes" ) {
			return RESTART;
		} else {
			return EXIT;
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.error_input;
		cout << endl << prompt.try_again;

		cont = get_string(maxLength);

		if( cont == "yes" ) {
			return RESTART;
		} else {
			return EXIT;
		}
	}// END try...catch

	return raw;
} // END METHOD getString

/* CLASS: Input
 * METHOD: get_string (overload)
 * DESCRIPTION: Gets valid string from user, repeats prompt which calls for the user input automatically.
 */
string Input::get_string(int maxLength, string prompt) {
	string raw;

	try {
		cout << endl << prompt;
		raw = get_string(maxLength);
		if( raw == RESTART ) {
			raw = get_string(maxLength, prompt);
		}
	} catch (...) {
		cout << "ERROR: General";
	} // END try...catch

	return raw;
} // END METHOD get_string

/* CLASS: Input
 * METHOD: get_integer
 * DESCRIPTION: Gets a valid integer value from the user within the range <min> to <max>
 				Returns -1 if invalid input
 */
int Input::get_integer(int min, int max) {
	string raw;
	int newValue;
	cout << "\n--> ";

	try {
		getline(cin,raw);
		try {
			newValue = stoi(raw);
		} catch (...) {
			cout << prompt.error_input << endl;
		}
		if(newValue > max)
			throw out_of_range("Input is above acceptable value");
		if(newValue < min)
			throw out_of_range("Input is below acceptable value");
	} catch (out_of_range x) {
		string cont;

		cout << endl << x.what();
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			throw invalid_argument(RESTART);
		} else {
			throw domain_error(EXIT);
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.soft_input;
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			newValue = get_integer(min, max);
		} else {
			throw domain_error(EXIT);
		}
	}// END try...catch

	return newValue;
} // END METHOD getInteger

/* CLASS: Input
 * METHOD: get_int (overload)
 * DESCRIPTION: Gets valid integer from user, repeats prompt which calls for the user input automatically.
 */
int Input::get_integer(int min, int max, string prompt) {
	int raw;

	try {
		cout << endl << prompt;
		raw = get_integer(min, max);
	} catch (domain_error x) {
		cout << x.what();
	} catch (invalid_argument x) {
		raw = get_integer(min, max, prompt);
	} catch (...) {

		cout << "ERROR: General";
	} // END try...catch

	return raw;
} // END METHOD get_integer

/* CLASS: Input
 * METHOD: get_float
 * DESCRIPTION: Gets a valid float value from the user within the range <min> to <max>
 				Returns -1 if invalid input
 */
float Input::get_float(float min, float max) {
	string raw;
	float newValue;
	cout << "\n--> ";

	try {
		getline(cin,raw);
		try {
			newValue = stof(raw);
		} catch (...) {
			cout << prompt.error_input << endl;
		}
		if(newValue > max)
			throw out_of_range("Input is above acceptable value");
		if(newValue < min)
			throw out_of_range("Input is below acceptable value");
	} catch (out_of_range x) {
		string cont;

		cout << endl << x.what();
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			throw invalid_argument(RESTART);
		} else {
			throw domain_error(EXIT);
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.soft_input;
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			throw invalid_argument(RESTART);
		} else {
			throw domain_error(EXIT);
		}
	}// END try...catch

	return newValue;
} // END METHOD get_float

/* CLASS: Input
 * METHOD: get_float (overload)
 * DESCRIPTION: Gets valid float from user, repeats prompt which calls for the user input automatically.
 */
float Input::get_float(float min, float max, string prompt) {
	float raw;

	try {
		cout << endl << prompt;
		raw = get_float(min, max);
	} catch (domain_error x) {
		cout << x.what();
	} catch (invalid_argument x) {
		raw = get_float(min, max, prompt);
	} catch (...) {

		cout << "ERROR: General";
	} // END try...catch

	return raw;
} // END METHOD get_float

class Account{
private:

protected:
	vector<string> names;
	vector<double> balance;
	int choice = 0;
	int length = 0;
	double amount = 0;
	int x = 0;
	int y = 0;

public:
	void ViewBalance(int);
	Account(string, string);
}; // END CLASS Account

class SavingsAccount:Account{
private:

protected:

public:
	SavingsAccount(string, string);

}; // END CLASS SavingsAccount

SavingsAccount::SavingsAccount(string file_name, string username):Account(file_name, username){
	fstream fptr;
	if(choice == 1){
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		balance[y] = balance[y] + amount;
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}

	}
	if(choice == 2){
		cout << prompt.withdraw << endl;
		cin >> amount;
		balance[y] = balance[y] - amount;
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}
	}
} // END CONSTRUCTOR SavingsAccount

class CheckingAccount:Account{
private:

protected:

public:
	CheckingAccount(string, string);

};

CheckingAccount::CheckingAccount(string file_name, string username):Account(file_name, username){
	//cout << "creating checking account" << endl;
	fstream fptr;
	//int x, y;
	if(choice == 1){
		cout << prompt.deposit << endl;
		cin >> amount;
		balance[y] = balance[y] + amount + (amount*.1);
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}

	}
	if(choice == 2){
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		balance[y] = balance[y] - amount;
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}
	}


} // END CONSTRUCTOR CheckingAccount

Account::Account(string file_name, string username){
	int length = 0;
	int x = 0;
	int y = 0;
	string a;
	double b;
	fstream fptr;
	fptr.open(file_name);
	if(!fptr.is_open()){
		cout << prompt.error_fileAccess << endl;
	}

	fptr >> length;
	for(x=0;x<length;x++){

		fptr >> a;
		names.push_back(a);
		//cout << names[x] << endl;
		fptr >> b;
		balance.push_back(b);
		//cout << balance[x] << endl;
	}

	for(x=0;x<length;x++){
		if(names[x] == username){
			cout << "\nHello " << username << endl;
			cout << prompt.info_balance << balance[x] << endl;
			y = x;
			cout << endl;
		}
	}

	fptr.close();
	int choice = 0;
	double amount;
	choice = userInput.get_integer(1, 3, prompt.menu_account);

	if(choice == 1){
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		balance[y] = balance[y] + amount;
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}

	}
	if(choice == 2){
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		balance[y] = balance[y] - amount;
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}
	}
	cout << "end" << endl;
}
class Customer{
private:
	int choice_c = 0;
	string username;
	string password;
	int length = 0;
	vector<string> names;
	vector<string> passwords;

public:
	Customer();
	int Customer_Menu();
	int Customer_login();
	string get_username();

}; // END CLASS Customer

string Customer::get_username(){
	return username;
}

Customer::Customer(){
	//enter username and password
	//open file to check
	//give option to return to main menu
}

int Customer::Customer_login(){
	int x = 0;
	int y = 0;
	string a;
	string b;
	int loop = 0;

	fstream fptr;
	fptr.open(DATA_CUSTOMER);
	if(!fptr.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr >> length;
	//cout << length << endl;
	for(x=0;x<length;x++){
		fptr >> a;
		names.push_back(a);
		fptr >> b;
		passwords.push_back(b);
		//cout << names[x] << endl;
		//cout << passwords[x] << endl;

	}
	fptr.close();
	while(loop == 0){
		username = userInput.get_string(MAX_NAME_LENGTH, prompt.username);
		if(username == EXIT){
			return 1;
		}
		password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);

	for(x=0;x<length;x++){
		if(names[x] == username && passwords[x] == password){
			cout << endl;
			cout << "welcome " << username << endl;
			loop = 1;
			break;
		}
	}
	if(x == length){
		cout << prompt.try_again_please << endl;
			continue;
	}
	}
	return 0;

}

int Customer::Customer_Menu(){
	choice_c = userInput.get_integer(1, 3, prompt.menu_customer);
	return choice_c;

}

class Employee{
private:
	int choice_e = 0;
	string username1;
	string username;
	string password;
	int length_c = 0;
	int length_e = 0;
	vector<string> names;
	vector<string> passwords;
	vector<double> payroll;
	vector<string> customer_names;
	vector<double> savings;
	vector<double> checking;
	vector<string> customer_passwords;

public:
	Employee();
	int Employee_Menu();
	int Employee_login();
	int Manage_Customer(string customer_name);
	int View_payroll();
	void View_All_Accounts();
	void Add_Withdraw(string customer_name, string file_name, int value);
	void Initialize();
	void Add_Customer();
	void Remove_Customer();
};

Employee::Employee(){

}

void Employee::Remove_Customer(){

	int x = 0;
	int y = 0;
	int temp;
	int loop = 0;
	string customer;

	while(loop == 0){
		customer = userInput.get_string(MAX_NAME_LENGTH, prompt.customer_name);
		for(x=0;x<length_c;x++){
			if(customer_names[x] == customer){
				loop = 1;
				y = x;
				break;
			}

		}
		if(x == length_c){
			cout << "not a valid customer" << endl;

		}
	}

	customer_names.erase(customer_names.begin()+y);
	customer_passwords.erase(customer_passwords.begin()+y);
	savings.erase(savings.begin()+y);
	checking.erase(checking.begin()+y);
	length_c = length_c - 1;

    fstream fptr1;
	fptr1.open(DATA_CUSTOMER, fstream::out);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr1 << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open(DATA_SAVINGS, fstream::out);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

    fstream fptr2;
	fptr2.open(DATA_CHECKING, fstream::out);
	if(!fptr2.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr2 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr2 << customer_names[x] << " " << checking[x] << endl;
	}
	fptr2.close();
}

void Employee::Add_Customer(){
	int x = 0;
	int loop = 0;
	string new_customer;
	string new_password;
	double new_savings;
	double new_checking;

	while(loop == 0){
		new_customer = userInput.get_string(MAX_NAME_LENGTH, prompt.new_customer_name);
		for(x=0;x<length_c;x++){
			if(customer_names[x] == new_customer){
				cout << prompt.soft_customer_name << endl;
				break;
			}
		}
		if(x == length_c){
			loop = 1;
		}
	}

	length_c = length_c + 1;

	new_password = userInput.get_string(MAX_PASS_LENGTH, prompt.new_customer_password);

	customer_names.push_back(new_customer);
	customer_passwords.push_back(new_password);

	fstream fptr;
	fptr.open(DATA_CUSTOMER);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr.close();

	new_savings = userInput.get_float(0, MAX_AMOUNT_ACCOUNT, prompt.new_customer_savings);
	savings.push_back(new_savings);

	new_checking = userInput.get_float(0, MAX_AMOUNT_ACCOUNT, prompt.new_customer_checking);
	checking.push_back(new_checking);

	//fstream fptr;
	fptr.open(DATA_SAVINGS);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

	//fstream fptr;
	fptr.open(DATA_CHECKING);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << checking[x] << endl;
	}
	fptr.close();

}

void Employee::Initialize(){

	string a, b, e, g, h;
	int x = 0;
	double c, d, f;

	fstream fptr1;
	fptr1.open(DATA_CUSTOMER);
	if(!fptr1.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr1 >> length_c;
	for(x=0;x<length_c;x++){
		fptr1 >> a;
		customer_names.push_back(a);
		fptr1 >> b;
		customer_passwords.push_back(b);
		//cout << customer_names[x] << endl;
		//cout << customer_passwords[x] << endl;
	}
	fptr1.close();

	fstream fptr2;
	fptr2.open(DATA_SAVINGS);
	if(!fptr2.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr2 >> length_c;
	for(x=0;x<length_c;x++){
		fptr2 >> a;
		fptr2 >> c;
		savings.push_back(c);
		//cout << savings[x] << endl;
	}
	fptr2.close();

	fstream fptr3;
	fptr3.open(DATA_CHECKING);
	if(!fptr3.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr3 >> length_c;
	for(x=0;x<length_c;x++){
		fptr3 >> a;
		fptr3 >> d;
		checking.push_back(d);
		//cout << checking[x] << endl;
	}
	fptr3.close();

	fstream fptr4;
	fptr4.open(DATA_PAYROLL);
	if(!fptr4.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr4 >> length_e;
	for(x=0;x<length_e;x++){
		fptr4 >> e;
		names.push_back(e);
		//cout << names[x] << endl;
		fptr4 >> f;
		payroll.push_back(f);
		//cout << payroll[x] << endl;
	}

	fstream fptr5;
	fptr5.open(DATA_EMPLOYEE);
	if(!fptr5.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr5 >> length_e;
	for(x=0;x<length_e;x++){
		fptr5 >> g;
		names.push_back(g);
		fptr5 >> h;
		passwords.push_back(h);
		//cout << names[x] << endl;
		//cout << passwords[x] << endl;
	}
	fptr5.close();
}



void Employee::Add_Withdraw(string customer_name, string file_name, int value){

	int x = 0;
	int y = 0;
	fstream fptr;

	for(x=0;x<length_c;x++){
		if(customer_names[x] == customer_name){
			cout << "\nhello " << customer_name << endl;
			//cout << "your balance is: $" << endl;
			y = x;
			cout << endl;
		}
	}

	int choice = 0;
	double amount;

	if(value == 1){
		cout << prompt.info_balance << savings[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		savings[y] = savings[y] + amount;
		cout << prompt.info_balance << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}

	}
	if(value == 2){
		cout << prompt.info_balance << checking[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		checking[y] = checking[y] + amount;
		cout << prompt.info_balance << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
	if(value == 3){
		cout << prompt.info_balance << savings[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		savings[y] = savings[y] - amount;
		cout << prompt.info_balance << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}
	}
	if(value == 4){
		cout << prompt.info_balance << checking[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		checking[y] = checking[y] - amount;
		cout << prompt.info_balance << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
}

void Employee::View_All_Accounts(){

	int x = 0;

	cout << "names     " << "savings   " << "checking  " << endl;
	for(x=0;x<length_c;x++){
		cout << customer_names[x] << "     " << savings[x] << "       " << checking[x] << "     " << endl;
	}

}

int Employee::View_payroll(){
	//uses private member username
	int x = 0;

	for(x=0;x<length_e;x++){
		if(names[x] == username){
			cout << "\nhello " << username << endl;
			cout << prompt.info_hourly_rate << payroll[x] << endl;
			cout << endl;
		}
	}
	return 0;
}

int Employee::Employee_Menu(){
	choice_e = userInput.get_integer(1, 6, prompt.menu_employee);
	return choice_e;
}

int Employee::Manage_Customer(string customer_name){

	int x = 0;
	int loop = 0;

	for(x=0;x<length_c;x++){
		if(customer_names[x] == customer_name){
			cout <<endl;
			loop = 1;
			return 1;
		}
	}
	if(x == 3){
		cout << prompt.try_again_please << endl;
		return 0;
	}
	return 2;
}

int Employee::Employee_login(){
	int x = 0;
	int loop = 0;

	while(loop == 0){
		username = userInput.get_string(MAX_NAME_LENGTH, prompt.username);
		if(username == EXIT){
			return 1;
		}

		password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);

	for(x=0;x<length_e;x++){
		if(names[x] == username && passwords[x] == password){
			cout << endl;
			cout << "welcome " << username << endl;
			loop = 1;
			break;
		}
	}
	if(x == 3){
		cout << prompt.try_again_please << endl;
			continue;
	}
	}
	return 0;

}

class Manager{
private:
	int length_c = 0;
	int length_e = 0;
	int length_m = 0;
	int choice_m = 0;
	string username;
	string password;
	vector<string> names;
	vector<string> passwords;
	vector<double> payroll;
	vector<string> customer_names;
	vector<double> savings;
	vector<double> checking;
	vector<string> customer_passwords;
	vector<string> employee_names;
	vector<string> employee_passwords;

public:
	Manager();
	int manager_menu();
	int manager_login();
	void Initialize();
	int Manage_Customer(string customer_name);
	void Add_Withdraw(string customer_name, string file_name, int value);
	void Add_Customer();
	void Remove_Customer();
	void View_All_Accounts();
	int Manage_Employee(string employee_name);
	void Change_Pay(string employee_name);
	void Add_Employee();
	void Remove_Employee();
	void View_All_Employee();

};

void Manager::View_All_Employee(){

	int x = 0;

	cout << "names     " << "pay rate" << endl;
	for(x=0;x<length_e;x++){
		cout << employee_names[x] << "     " << payroll[x]      << endl;
	}

}


void Manager::Remove_Employee(){

	int x = 0;
	int y = 0;
	int temp;
	int loop = 0;
	string employee;

	while(loop == 0){
		cout << "enter name of employee" << endl;
		cin >> employee;
		for(x=0;x<length_e;x++){
			if(employee_names[x] == employee){
				loop = 1;
				y = x;
				break;
			}

		}
		if(x == length_e){
			cout << "not a valid employee" << endl;
		}
	}

	employee_names.erase(employee_names.begin()+y);
	employee_passwords.erase(employee_passwords.begin()+y);
	payroll.erase(payroll.begin()+y);
	length_e = length_e - 1;

	for(x=0;x<length_e;x++){
		cout << employee_names[x] << endl;
		cout << employee_passwords[x] << endl;
	}

    fstream fptr1;
	fptr1.open(DATA_EMPLOYEE, fstream::out);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr1 << employee_names[x] << " " << employee_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open(DATA_PAYROLL, fstream::out);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr << employee_names[x] << " " << payroll[x] << endl;
	}
	fptr.close();
}

void Manager::Add_Employee(){
	string new_employee;
	string new_password;
	double new_pay;
	int loop = 0;
	int x = 0;

	while(loop == 0){
		cout << "Enter the name of the employee" << endl;
		cin >> new_employee;
		for(x=0;x<length_e;x++){
			if(employee_names[x] == new_employee){
				cout << "there is already an employee with that name" << endl;
				break;
			}
		}
		if(x == length_e){
			loop = 1;
		}
	}

	length_e = length_e + 1;

	cout << prompt.password << endl;
	cin >> new_password;
	employee_passwords.push_back(new_password);

	cout << "enter the new pay for this customer" << endl;
	cin >> new_pay;
	employee_names.push_back(new_employee);
	payroll.push_back(new_pay);


	fstream fptr;
	fptr.open(DATA_PAYROLL);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr << employee_names[x] << " " << payroll[x] << endl;
	}
	fptr.close();

	fstream fptr1;
	fptr1.open(DATA_EMPLOYEE);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr1 << employee_names[x] << " " << employee_passwords[x] << endl;
	}
	fptr1.close();

}

void Manager::Change_Pay(string employee_name){

	int x = 0;
	int y = 0;
	fstream fptr;
	double new_pay;
	string file_name = DATA_PAYROLL;

	for(x=0;x<length_e;x++){
		if(employee_names[x] == employee_name){
			//cout << "\nhello " << employee_name << endl;
			//cout << "your balance is: $" << endl;
			y = x;
			cout << endl;
		}
	}

			cout << "current pay is: " << payroll[y] << endl;
			cout << "Enter new pay rate" << endl;
			cin >> new_pay;
			payroll[y] = new_pay;
			cout << "new pay rate is: " << payroll[y] << endl;
			fptr.open(file_name);
			if(!fptr.is_open()){
					cout << "could not open file" << endl;
			}
			fptr << length_e << endl;
			for(x=0;x<length_e;x++){
				fptr << employee_names[x] << " " << payroll[x] << endl;
			}

			fptr.close();

}

int Manager::Manage_Employee(string employee_name){


	int x = 0;
	int loop = 0;

	for(x=0;x<length_e;x++){
		if(employee_names[x] == employee_name){
			cout << endl;
			loop = 1;
			return 1;
		}
	}
	if(x == length_e){
		cout << "please try again" << endl;
		return 0;
	}
	return 2;

}

void Manager::View_All_Accounts(){

	int x = 0;

	cout << "names     " << "savings   " << "checking  " << endl;
	for(x=0;x<length_c;x++){
		cout << customer_names[x] << "     " << savings[x] << "       " << checking[x] << "     " << endl;
	}

}

void Manager::Remove_Customer(){

	int x = 0;
	int y = 0;
	int temp;
	int loop = 0;
	string customer;

	while(loop == 0){
		cout << "enter name of customer" << endl;
		cin >> customer;
		for(x=0;x<length_c;x++){
			if(customer_names[x] == customer){
				loop = 1;
				y = x;
				break;
			}

		}
		if(x == length_c){
			cout << "not a valid customer" << endl;
		}
	}

	customer_names.erase(customer_names.begin()+y);
	customer_passwords.erase(customer_passwords.begin()+y);
	savings.erase(savings.begin()+y);
	checking.erase(checking.begin()+y);
	length_c = length_c - 1;

    fstream fptr1;
	fptr1.open(DATA_CUSTOMER, fstream::out);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr1 << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open(DATA_SAVINGS, fstream::out);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

    fstream fptr2;
	fptr2.open(DATA_CHECKING, fstream::out);
	if(!fptr2.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr2 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr2 << customer_names[x] << " " << checking[x] << endl;
	}
	fptr2.close();
}

void Manager::Add_Customer(){
	int x = 0;
	int loop = 0;
	string new_customer;
	string new_password;
	double new_savings;
	double new_checking;

	while(loop == 0){
		new_customer = userInput.get_string(MAX_NAME_LENGTH, prompt.customer_name);
		for(x=0;x<length_c;x++){
			if(customer_names[x] == new_customer){
				cout << "there is already a customer with that name" << endl;
				break;
			}
		}
		if(x == length_c){
			loop = 1;
		}
	}

	length_c = length_c + 1;

	new_password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);
	customer_names.push_back(new_customer);
	customer_passwords.push_back(new_password);

	fstream fptr;
	fptr.open(DATA_CUSTOMER);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr.close();

	cout << "enter savings balance for new customer" << endl;
	cin >> new_savings;
	savings.push_back(new_savings);
	cout << "enter checking balance for new customer" << endl;
	cin >> new_checking;
	checking.push_back(new_checking);

	//fstream fptr;
	fptr.open(DATA_SAVINGS);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

	//fstream fptr;
	fptr.open(DATA_CHECKING);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << checking[x] << endl;
	}
	fptr.close();

}

void Manager::Add_Withdraw(string customer_name, string file_name, int value){

	int x = 0;
	int y = 0;
	fstream fptr;

	for(x=0;x<length_c;x++){
		if(customer_names[x] == customer_name){
			cout << "\nhello " << customer_name << endl;
			//cout << "your balance is: $" << endl;
			y = x;
			cout << endl;
		}
	}

	int choice = 0;
	double amount;

	if(value == 1){
		cout << prompt.info_balance << savings[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		savings[y] = savings[y] + amount;
		cout << prompt.info_balance << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}

	}
	if(value == 2){
		cout << prompt.info_balance << checking[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		checking[y] = checking[y] + amount;
		cout << prompt.info_balance << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
	if(value == 3){
		cout << prompt.info_balance << savings[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		savings[y] = savings[y] - amount;
		cout << prompt.info_balance << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}
	}
	if(value == 4){
		cout << prompt.info_balance << checking[y] << endl;
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		checking[y] = checking[y] - amount;
		cout << prompt.info_balance << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
}


int Manager::Manage_Customer(string customer_name){

	int x = 0;
	int loop = 0;

	for(x=0;x<length_c;x++){
		if(customer_names[x] == customer_name){
			cout <<endl;
			loop = 1;
			return 1;
		}
	}
	if(x == length_c){
		cout << prompt.try_again_please << endl;
		return 0;
	}
	return 2;
}

int Manager::manager_login(){

	int x = 0;
	int loop = 0;

	while(loop == 0){
		username = userInput.get_string(MAX_NAME_LENGTH, prompt.username);
		if(username == EXIT){
			return 1;
		}
		password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);

	for(x=0;x<length_e;x++){
		if(names[x] == username && passwords[x] == password){
			cout << endl;
			cout << "welcome " << username << endl;
			loop = 1;
			break;
		}
	}
	if(x == 3){
		cout << prompt.try_again_please << endl;
			continue;
	}
	}
	return 0;
}

void Manager::Initialize(){

	string a, b, e, g, h, i, j;
	int x = 0;
	double c, d, f;

	fstream fptr1;
	fptr1.open(DATA_CUSTOMER);
	if(!fptr1.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr1 >> length_c;
	for(x=0;x<length_c;x++){
		fptr1 >> a;
		customer_names.push_back(a);
		fptr1 >> b;
		customer_passwords.push_back(b);
		//cout << customer_names[x] << endl;
		//cout << customer_passwords[x] << endl;
	}
	fptr1.close();

	fstream fptr2;
	fptr2.open(DATA_SAVINGS);
	if(!fptr2.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr2 >> length_c;
	for(x=0;x<length_c;x++){
		fptr2 >> a;
		fptr2 >> c;
		savings.push_back(c);
		//cout << savings[x] << endl;
	}
	fptr2.close();

	fstream fptr3;
	fptr3.open(DATA_CHECKING);
	if(!fptr3.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr3 >> length_c;
	for(x=0;x<length_c;x++){
		fptr3 >> a;
		fptr3 >> d;
		checking.push_back(d);
		//cout << checking[x] << endl;
	}
	fptr3.close();

	fstream fptr4;
	fptr4.open(DATA_PAYROLL);
	if(!fptr4.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr4 >> length_e;
	for(x=0;x<length_e;x++){
		fptr4 >> e;
		names.push_back(e);
		//cout << names[x] << endl;
		fptr4 >> f;
		payroll.push_back(f);
		//cout << payroll[x] << endl;
	}

	fstream fptr5;
	fptr5.open(DATA_EMPLOYEE);
	if(!fptr5.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr5 >> length_e;
	for(x=0;x<length_e;x++){
		fptr5 >> g;
		employee_names.push_back(g);
		fptr5 >> h;
		employee_passwords.push_back(h);
		//cout << names[x] << endl;
		//cout << passwords[x] << endl;
	}
	fptr5.close();

	fstream fptr6;
	fptr6.open(DATA_MANAGER);
	if(!fptr6.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr6 >> length_m;
	for(x=0;x<length_m;x++){
		fptr6 >> i;
		names.push_back(i);
		fptr6 >> j;
		passwords.push_back(j);
		//cout << names[x] << endl;
		//cout << passwords[x] << endl;
	}
	fptr6.close();
}

int Manager::manager_menu(){
	choice_m = userInput.get_integer(0, 3, prompt.menu_manager);
	return choice_m;
}

Manager::Manager(){

}

int menu(){
	int choice = 0;
	string a;
	choice = userInput.get_integer(1, 5, prompt.menu_main);
	return choice;
}

int main(void){
	int choice;
	int choice_c;
	int choice_e;
	int return_to_main = 0;
	int thing1 = 0;
	int thing2 = 0;
	int second_loop = 0;

	string c = DATA_CHECKING;
	string s = DATA_SAVINGS;

	string username;
	string customer_name;
	int x, y;
	int choice_m1;
	int choice_m2;
	int choice_m3;
	string employee_name;
	Customer customer1;
	Employee employee1;
	Manager manager1;
	int third_loop = 0;

	while(return_to_main == 0){

		choice = menu();

		switch (choice){
		case 1:
			//Customer customer1;
			thing1 = customer1.Customer_login();

			username = customer1.get_username();

			if(thing1 == 1){
				continue;
			}
			second_loop = 0;
			while(second_loop == 0){
				choice_c = customer1.Customer_Menu();
				if(choice_c == 1){
					CheckingAccount checking(c, username);

				}
				if(choice_c == 2){
					SavingsAccount savings(s, username);
				}
				if(choice_c == 3){
					second_loop = 1;
				}
			}
			break;


		case 2:

			//Employee employee1;
			employee1.Initialize();
			thing2 = employee1.Employee_login();
			if(thing2 == 1){
				continue;
			}
			second_loop = 0;
			while(second_loop == 0){
				choice_e = employee1.Employee_Menu();
				while(choice_e == 1){
					customer_name = userInput.get_string(MAX_NAME_LENGTH, prompt.manager_customer);
					if(customer_name == EXIT){
						choice_e = 0;
						continue;
					}
					x = employee1.Manage_Customer(customer_name);
					if(x == 0){
						cout << "not a valid customer" << endl;
					}
					if(x == 1){
						cout << "good job" << endl;
						int x = userInput.get_integer(0, 4, prompt.menu_addRemove);
						if(x == 1)
							employee1.Add_Withdraw(customer_name, DATA_SAVINGS, 1);
						if(x == 2)
							employee1.Add_Withdraw(customer_name, DATA_CHECKING, 2);
						if(x == 3)
							employee1.Add_Withdraw(customer_name, DATA_SAVINGS, 3);
						if(x == 4)
							employee1.Add_Withdraw(customer_name, DATA_CHECKING, 4);
						choice_e = 0;
					}
				}
				if(choice_e == 2){
					employee1.View_payroll();
				}
				if(choice_e == 3){
					employee1.Add_Customer();
				}
				if(choice_e == 4){
					//remove customer
					employee1.Remove_Customer();

				}
				if(choice_e == 5){
					//view all accounts
					employee1.View_All_Accounts();
				}
				if(choice_e == 6){
					//exit loop
					second_loop = 1;
				}
			}

		break;

		case 3:
			//cout << "we haven't written that yet" << endl;
			//Manager manager1;
			manager1.Initialize();
			manager1.manager_login();
			choice_m1 = manager1.manager_menu();
			//int third_loop = 0;
			while(third_loop == 0){
			if(choice_m1 == 1){
				//manage customers
				choice_m2 = userInput.get_integer(0, 4, prompt.menu_manage_customer);
				while(choice_m2 == 1){
					customer_name = userInput.get_string(MAX_NAME_LENGTH, prompt.manager_customer);
					if(customer_name == EXIT){
						choice_m2 = 0;
						continue;
					}
					x = manager1.Manage_Customer(customer_name);
					if(x == 0){
						cout << "not a valid customer" << endl;
					}
					if(x == 1){
						cout << "good job" << endl;
						//add or remove funds from savings and checking
						int x = 0;
						x = userInput.get_integer(0, 5, prompt.menu_addRemove);
						if(x == 1)
							manager1.Add_Withdraw(customer_name, DATA_SAVINGS, 1);
						if(x == 2)
							manager1.Add_Withdraw(customer_name, DATA_CHECKING, 2);
						if(x == 3)
							manager1.Add_Withdraw(customer_name, DATA_SAVINGS, 3);
						if(x == 4)
							manager1.Add_Withdraw(customer_name, DATA_CHECKING, 4);
						choice_e = 0;
					}
				}
				if(choice_m2 == 2){
					manager1.Add_Customer();
				}
				if(choice_m2 == 3){
					//remove customer
					manager1.Remove_Customer();
				}
				if(choice_m2 == 4){
					manager1.View_All_Accounts();
				}
				if(choice_m2 == 5){
					choice_m1 = 0;
				}
			}

			if(choice_m1 == 2){
				//manage employees
				choice_m3 = userInput.get_integer(0, 5, prompt.menu_manageEmployees);
				while(choice_m3 == 1){
					employee_name = userInput.get_string(MAX_NAME_LENGTH, prompt.manager_employee);
					cout << "1" << endl;
					if(employee_name == EXIT){
						choice_m3 = 0;
						cout << "2" << endl;
						continue;
					}
					cout << "3" << endl;
					y = manager1.Manage_Employee(employee_name);
					cout << "4" << endl;
					if(y == 0){
						cout << "not a valid employee" << endl;
					}
					if(y == 1){
						manager1.Change_Pay(employee_name);
						choice_m3 = 0;
					}
				}
				if(choice_m3 == 2){
					//add employee
					manager1.Add_Employee();
				}
				if(choice_m3 == 3){
					//remove employee
					manager1.Remove_Employee();
				}
				if(choice_m3 == 4){
					//view all
					manager1.View_All_Employee();

				}
				if(choice_m3 == 5){
					//exit
					third_loop = 1;
				}
			if(choice_m1 == 3){
				//loop = 1;
			}
			}


		break;
		case 4:
			//cout << "we haven't written that yet" << endl;
			//creates a new customer account
			employee1.Initialize();
			employee1.Add_Customer();
		break;
		case 5:
			cout << "thanks for using this random bank" << endl;
			return 3;
		break;
		default:
			cout << "incorrect input" << endl;
			return 4;
		}
	}
	}
	return 0;
}
