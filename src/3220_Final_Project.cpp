#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

#define MAX_NAME_LENGTH 20
#define MAX_PASS_LENGTH 20
#define MAX_AMOUNT_DEPOSIT_WITHDRAW 1000000000
#define MAX_AMOUNT_ACCOUNT 1000000000

#define RESTART "***RESTART***"
#define EXIT "***EXIT***"

/* STRUCTURE: prompts
 * DESCRIPTION: Stores all of the prompts to be displayed to the user
 */
struct prompts {
	// Menu prompts
	string menu_main = "Enter 1 to Log in as a Customer\nEnter 2 to log in as an Employee\nEnter 3 to Log in as a Manager\nEnter 4 to Request New Customer Account\nEnter 5 to Exit";
	string menu_account = "Enter 1 to Add Funds\nEnter 2 to Withdraw Funds\nEnter 3 to Return to Exit Menu";
	string menu_customer = "Enter 1 to Manage Checking Account\nEnter 2 to Manage Savins Account\nEnter 3 to Exit Menu";
	string menu_employee = "Enter 1 to Manage a Customer Account\nEnter 2 to View Payroll Information\nEnter 3 to Add Customer Account\nEnter 4 to Remove Customer Account\nEnter 5 to View All Customer Accounts\nEnter 6 to Exit Menu";
	string menu_manage_customer = "Enter 1 to Add Funds to Savings\nEnter 2 to Add Funds to Checking\nEnter 3 to Withdraw From Savings\nEnter 4 to Withdraw from Checking";
	string menu_customer_account_name = "Which Customer Account Would you Like to Manage?\n(Enter 'exit' to Exit Menu)";
	
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
	string try_again = "Would you like to try again? (yes) -or- (no): ";
	string exit = "Enter 'exit' to Exit Current Menu";
	
	// New customer data acquisition
	string new_customer_name = "Enter Name of New Customer: ";
	string new_customer_password = "Enter Password of New Customer: ";
	string new_customer_checking = "Enter Checking Balance for New Customer: ";
	string new_customer_savings = "Enter Savings Balance for New Customer: ";
	
	// Error messages
	string error_general = "ERROR: General Error";
	string error_fileAccess = "ERROR: Unable to open file";
	string error_input = "ERROR: Invalid Input";
	string error_characterOverflow = "ERROR: Too many characters";
}prompt;

/* STRUCTURE: data_file
 * DESCRIPTION: Holds the name of the data files
 */
struct data_file {
	string customer = "customers.txt";
}file;

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
	} catch (length_error x) {
		string cont;

		cout << endl << x.what();
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			return RESTART;
		} else {
			return EXIT;
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.error_input;
		cout << endl << prompt.try_again;

		cont = get_string(3);

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
			newValue = get_integer(min, max);
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
			newValue = get_float(min, max);
		} else {
			throw domain_error(EXIT);
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.soft_input;
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			newValue = get_float(min, max);
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

public:
	void ViewBalance(int);
	Account(string, string);

};

class SavingsAccount:Account{
private:

protected:

public:
	SavingsAccount(string, string);

};
SavingsAccount::SavingsAccount(string file_name, string username):Account(file_name, username){
	cout << "creating savings account" << endl;
}
class CheckingAccount:Account{
private:

protected:

public:
	CheckingAccount(string, string);

};

CheckingAccount::CheckingAccount(string file_name, string username):Account(file_name, username){
	//cout << "creating checking account" << endl;
}

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
	//cout << file_name << endl;
	fptr >> length;
	//cout << length << endl;
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

};
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
	fptr.open("customers.txt");
	if(!fptr.is_open()){
		cout << "could not open file" << endl;
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
		if(username == "exit"){
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
		cout << "please try again" << endl;
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

};

Employee::Employee(){

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
	fptr.open(file.customer);
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
	fptr.open("savings.txt");
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

	//fstream fptr;
	fptr.open("checking.txt");
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
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
	fptr1.open("customers.txt");
	if(!fptr1.is_open()){
		cout << "could not open file" << endl;
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
	fptr2.open("savings.txt");
	if(!fptr2.is_open()){
		cout << "could not open file" << endl;
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
	fptr3.open("checking.txt");
	if(!fptr3.is_open()){
		cout << "could not open file" << endl;
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
	fptr4.open("payroll.txt");
	if(!fptr4.is_open()){
		cout << "could not open file" << endl;
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
	fptr5.open("employees.txt");
	if(!fptr5.is_open()){
		cout << "could not open file" << endl;
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
		cout << "please try again" << endl;
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
		cout << "please try again" << endl;
			continue;
	}
	}
	return 0;

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

	string c = "checking.txt";
	string s = "savings.txt";
	
	string username;

	while(return_to_main == 0){

		choice = menu();

		if(choice == 1){
			Customer customer1;
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
		}
		string customer_name;
		int x;
		if(choice == 2){

			Employee employee1;
			employee1.Initialize();
			thing2 = employee1.Employee_login();
			if(thing2 == 1){
				continue;
			}
			second_loop = 0;
			while(second_loop == 0){
				choice_e = employee1.Employee_Menu();
				while(choice_e == 1){
					customer_name = userInput.get_string(MAX_NAME_LENGTH, prompt.menu_customer_account_name);
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
						//add or remove funds from savings and checking
						int x = userInput.get_integer(1, 4, prompt.menu_manage_customer);
						if(x == 1)
							employee1.Add_Withdraw(customer_name, "savings.txt", 1);
						if(x == 2)
							employee1.Add_Withdraw(customer_name, "checking.txt", 2);
						if(x == 3)
							employee1.Add_Withdraw(customer_name, "savings.txt", 3);
						if(x == 4)
							employee1.Add_Withdraw(customer_name, "checking.txt", 4);
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
		}
		if(choice == 3){
			cout << "we haven't written that yet" << endl;
		}
		if(choice == 4){
			//cout << "we haven't written that yet" << endl;
			//creates a new customer account
		}
		if(choice == 5){
			cout << "thanks for using this random bank" << endl;
			return 3;
		}
	}
	return 0;
}
