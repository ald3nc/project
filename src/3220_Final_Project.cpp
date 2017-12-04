#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int menu();
					//checking account - % bonus for deposit
					//savings account - normal deposit
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

};

class SavingsAccount:Account{
private:

protected:

public:
	SavingsAccount(string, string);

};
SavingsAccount::SavingsAccount(string file_name, string username):Account(file_name, username){
	//cout << "creating savings account" << endl;
	fstream fptr;
	if(choice == 1){
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		balance[y] = balance[y] + amount;
		cout << "your new balance is: " << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}

	}
	if(choice == 2){
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		balance[y] = balance[y] - amount;
		cout << "your new balance is: " << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}
	}


}
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
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		balance[y] = balance[y] + amount + (amount*.1);
		cout << "your new balance is: " << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}

	}
	if(choice == 2){
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		balance[y] = balance[y] - amount;
		cout << "your new balance is: " << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}
	}


}
Account::Account(string file_name, string username){
	string a;
	double b;
	fstream fptr;
	fptr.open(file_name);
	if(!fptr.is_open()){
		cout << "could not open file" << endl;
	}
	fptr >> length;
	for(x=0;x<length;x++){

		fptr >> a;
		names.push_back(a);
		fptr >> b;
		balance.push_back(b);
	}
	for(x=0;x<length;x++){
		if(names[x] == username){
			cout << "\nhello " << username << endl;
			cout << "your balance is: $" << balance[x] << endl;
			y = x;
			cout << endl;
		}
	}
	fptr.close();
	cout << "\nEnter 1 to add funds" << endl;
	cout << "Enter 2 to withdraw funds" << endl;
	cout << "Enter 3 to return to exit menu" << endl;
	cin >> choice;

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
		cout << "enter 'exit' as your username to return to main menu" << endl;
		cout << "enter your username" << endl;
		cin >> username;
		if(username == "exit"){
			return 1;
		}
		cout << "enter your password" << endl;
		cin >> password;

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
	cout << "\nEnter 1 to manage checking account" << endl;			//savings/checking?
	cout << "Enter 2 to manage savings account" << endl;
	cout << "Enter 3 to exit menu" << endl;
	cin >> choice_c;				//need to error check choice_c
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
	fptr1.open("customers.txt", fstream::out);
	if(!fptr1.is_open()){
			cout << "could not open file" << endl;
	}
	fptr1 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr1 << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open("savings.txt", fstream::out);
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
	}
	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

    fstream fptr2;
	fptr2.open("checking.txt", fstream::out);
	if(!fptr2.is_open()){
			cout << "could not open file" << endl;
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
		cout << "Enter the name of the customer" << endl;
		cin >> new_customer;
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

	cout << "enter the password for this customer" << endl;
	cin >> new_password;
	customer_names.push_back(new_customer);
	customer_passwords.push_back(new_password);

	fstream fptr;
	fptr.open("customers.txt");
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
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
		cout << "your balance is: $" << savings[y] << endl;
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		savings[y] = savings[y] + amount;
		cout << "your new balance is: " << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}

	}
	if(value == 2){
		cout << "your balance is: $" << checking[y] << endl;
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		checking[y] = checking[y] + amount;
		cout << "your new balance is: " << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
	if(value == 3){
		cout << "your balance: $" << savings[y] << endl;
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		savings[y] = savings[y] - amount;
		cout << "your new balance is: " << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}
	}
	if(value == 4){
		cout << "your balance: $" << checking[y] << endl;
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		checking[y] = checking[y] - amount;
		cout << "your new balance is: " << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
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
			cout << "your hourly rate is: $" << payroll[x] << endl;
			cout << endl;
		}
	}
	return 0;
}

int Employee::Employee_Menu(){
	cout << "Enter 1 to manage a customer account" << endl;
	cout << "Enter 2 to view payroll information" << endl;
	cout << "Enter 3 to add customer account" << endl;
	cout << "Enter 4 to remove customer account" << endl;
	cout << "Enter 5 to view all customer accounts" << endl;
	cout << "Enter 6 to exit menu" << endl;
	cin >> choice_e;
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
		cout << "enter 'exit' as your username to return to main menu" << endl;
		cout << "enter your username" << endl;
		cin >> username;
		if(username == "exit"){
			return 1;
		}
		cout << "enter your password" << endl;
		cin >> password;

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
	fptr1.open("employees.txt", fstream::out);
	if(!fptr1.is_open()){
			cout << "could not open file" << endl;
	}
	fptr1 << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr1 << employee_names[x] << " " << employee_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open("payroll.txt", fstream::out);
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
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

	cout << "enter the password for this customer" << endl;
	cin >> new_password;
	employee_passwords.push_back(new_password);

	cout << "enter the new pay for this customer" << endl;
	cin >> new_pay;
	employee_names.push_back(new_employee);
	payroll.push_back(new_pay);


	fstream fptr;
	fptr.open("payroll.txt");
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
	}

	fptr << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr << employee_names[x] << " " << payroll[x] << endl;
	}
	fptr.close();

	fstream fptr1;
	fptr1.open("employees.txt");
	if(!fptr1.is_open()){
			cout << "could not open file" << endl;
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
	string file_name = "payroll.txt";

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
	fptr1.open("customers.txt", fstream::out);
	if(!fptr1.is_open()){
			cout << "could not open file" << endl;
	}
	fptr1 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr1 << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open("savings.txt", fstream::out);
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
	}
	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

    fstream fptr2;
	fptr2.open("checking.txt", fstream::out);
	if(!fptr2.is_open()){
			cout << "could not open file" << endl;
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
		cout << "Enter the name of the customer" << endl;
		cin >> new_customer;
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

	cout << "enter the password for this customer" << endl;
	cin >> new_password;
	customer_names.push_back(new_customer);
	customer_passwords.push_back(new_password);

	fstream fptr;
	fptr.open("customers.txt");
	if(!fptr.is_open()){
			cout << "could not open file" << endl;
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
		cout << "your balance is: $" << savings[y] << endl;
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		savings[y] = savings[y] + amount;
		cout << "your new balance is: " << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}

	}
	if(value == 2){
		cout << "your balance is: $" << checking[y] << endl;
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		checking[y] = checking[y] + amount;
		cout << "your new balance is: " << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
	if(value == 3){
		cout << "your balance: $" << savings[y] << endl;
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		savings[y] = savings[y] - amount;
		cout << "your new balance is: " << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length_c << endl;
		for(x=0;x<length_c;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}
	}
	if(value == 4){
		cout << "your balance: $" << checking[y] << endl;
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		checking[y] = checking[y] - amount;
		cout << "your new balance is: " << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
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
		cout << "please try again" << endl;
		return 0;
	}
	return 2;
}

int Manager::manager_login(){

	int x = 0;
	int loop = 0;

	while(loop == 0){
		cout << "enter 'exit' as your username to return to main menu" << endl;
		cout << "enter your username" << endl;
		cin >> username;
		if(username == "exit"){
			return 1;
		}
		cout << "enter your password" << endl;
		cin >> password;

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

void Manager::Initialize(){

	string a, b, e, g, h, i, j;
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
		employee_names.push_back(g);
		fptr5 >> h;
		employee_passwords.push_back(h);
		//cout << names[x] << endl;
		//cout << passwords[x] << endl;
	}
	fptr5.close();

	fstream fptr6;
	fptr6.open("managers.txt");
	if(!fptr6.is_open()){
		cout << "could not open file" << endl;
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
	cout << "Enter 1 to manage customers" << endl;
	cout << "Enter 2 to manage employees" << endl;
	cout << "Enter 3 to exit menu" << endl;
	cin >> choice_m;
	return choice_m;
}

Manager::Manager(){

}

int menu(){
	int choice = 0;
	string a;
	cout << "\nEnter 1 to log in as a customer" << endl;		//create customer class
	cout << "Enter 2 to log in as an employee" << endl;		//employee class
	cout << "Enter 3 to log in as a manager" << endl;		//manager class
	cout << "Enter 4 to request new customer account" << endl;		//employee class
	cout << "Enter 5 to exit" << endl;

	cin >> choice;		//need to error check choice here



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
					cout << "which customer account would you like to manage:" << endl;
					cout << "enter 'exit' to exit menu" << endl;
					cin >> customer_name;
					if(customer_name == "exit"){
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
						int x = 0;
						cout << "enter 1 to add funds to savings" << endl;
						cout << "enter 2 to add funds to checking" << endl;
						cout << "enter 3 to withdraw from savings" << endl;
						cout << "enter 4 to withdraw from checking" << endl;
						cin >> x;
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
				cout << "Enter 1 to manage a customer account" << endl;
				cout << "Enter 2 to add a new customer" << endl;
				cout << "Enter 3 to remove a customer" << endl;
				cout << "Enter 4 to view all accounts" << endl;
				cin >> choice_m2;
				while(choice_m2 == 1){
					cout << "which customer account would you like to manage:" << endl;
					cout << "enter 'exit' to exit menu" << endl;
					cin >> customer_name;
					if(customer_name == "exit"){
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
						cout << "enter 1 to add funds to savings" << endl;
						cout << "enter 2 to add funds to checking" << endl;
						cout << "enter 3 to withdraw from savings" << endl;
						cout << "enter 4 to withdraw from checking" << endl;
						cout << "enter 5 to exit menu" << endl;
						cin >> x;
						if(x == 1)
							manager1.Add_Withdraw(customer_name, "savings.txt", 1);
						if(x == 2)
							manager1.Add_Withdraw(customer_name, "checking.txt", 2);
						if(x == 3)
							manager1.Add_Withdraw(customer_name, "savings.txt", 3);
						if(x == 4)
							manager1.Add_Withdraw(customer_name, "checking.txt", 4);
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
				cout << "enter 1 to change an employees' pay" << endl;
				cout << "enter 2 to add an employee" << endl;
				cout << "enter 3 to remove an employee" << endl;
				cout << "enter 4 to view all employees" << endl;
				cout << "enter 5 to exit menu" << endl;
				cin >> choice_m3;
				while(choice_m3 == 1){
					cout << "which employee would you like to manage:" << endl;
					cout << "enter 'exit' to exit menu" << endl;
					cin >> employee_name;
					cout << "1" << endl;
					if(employee_name == "exit"){
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















