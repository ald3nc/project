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
		cout << "could not open file" << endl;
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
			cout << "\nhello " << username << endl;
			cout << "your balance is: $" << balance[x] << endl;
			y = x;
			cout << endl;
		}
	}
	fptr.close();
	int choice = 0;
	double amount;
	cout << "\nEnter 1 to add funds" << endl;
	cout << "Enter 2 to withdraw funds" << endl;
	cout << "Enter 3 to return to exit menu" << endl;
	cin >> choice;

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
	if(x == 3){
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
	int length = 0;
	vector<string> names;
	vector<string> passwords;
	vector<double> payroll;
	vector<string> customer_names;
	vector<double> savings;
	vector<double> checking;

public:
	Employee();
	int Employee_Menu();
	int Employee_login();
	int Manage_Customer(string customer_name);
	int View_payroll();
	void View_All_Accounts();
	void Add_Withdraw(string customer_name, string file_name, int value);

};

Employee::Employee(){

}

void Employee::Add_Withdraw(string customer_name, string file_name, int value){

	int x = 0;
	int y = 0;
	string a;
	double c,d;
	double b;
	fstream fptr;


	fstream fptr2;
	fptr2.open("savings.txt");
	if(!fptr2.is_open()){
		cout << "could not open file" << endl;
	}
	fptr2 >> length;
	for(x=0;x<length;x++){
		fptr2 >> a;
		fptr2 >> c;
		savings.push_back(c);
		cout << savings[x] << endl;
	}
	fptr2.close();

	fstream fptr3;
	fptr3.open("checking.txt");
	if(!fptr3.is_open()){
		cout << "could not open file" << endl;
	}
	fptr3 >> length;
	for(x=0;x<length;x++){
		fptr3 >> a;
		fptr3 >> d;
		checking.push_back(d);
		cout << checking[x] << endl;
	}
	fptr3.close();
	for(x=0;x<length;x++){
		if(customer_names[x] == customer_name){
			cout << "\nhello " << customer_name << endl;
			cout << "your balance is: $" << endl;
			y = x;
			cout << endl;
		}
	}

	int choice = 0;
	double amount;

	if(value == 1){
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		savings[y] = savings[y] + amount;
		cout << "your new balance is: " << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}

	}
	if(value == 2){
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		checking[y] = checking[y] + amount;
		cout << "your new balance is: " << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
	if(value == 3){
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		savings[y] = savings[y] - amount;
		cout << "your new balance is: " << savings[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << customer_names[x] << " " << savings[x] << endl;
		}
	}
	if(value == 4){
		cout << "Enter amount you would like to withdraw" << endl;
		cin >> amount;
		checking[y] = checking[y] - amount;
		cout << "your new balance is: " << checking[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << "could not open file" << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << customer_names[x] << " " << checking[x] << endl;
		}
	}
}

void Employee::View_All_Accounts(){

	int x = 0;
	int y = 0;
	string a;
	string b;
	double c,d;
	int loop = 0;

	fstream fptr1;
	fptr1.open("customers.txt");
	if(!fptr1.is_open()){
		cout << "could not open file" << endl;
	}
	fptr1 >> length;
	for(x=0;x<length;x++){
		fptr1 >> a;
		customer_names.push_back(a);
		fptr1 >> b;
	}
	fptr1.close();

	fstream fptr2;
	fptr2.open("savings.txt");
	if(!fptr2.is_open()){
		cout << "could not open file" << endl;
	}
	fptr2 >> length;
	for(x=0;x<length;x++){
		fptr2 >> a;
		fptr2 >> c;
		savings.push_back(c);
	}
	fptr2.close();

	fstream fptr3;
	fptr3.open("checking.txt");
	if(!fptr3.is_open()){
		cout << "could not open file" << endl;
	}
	fptr3 >> length;
	for(x=0;x<length;x++){
		fptr3 >> a;
		fptr3 >> d;
		checking.push_back(d);
	}
	fptr3.close();

	cout << "names     " << "savings   " << "checking  " << endl;
	for(x=0;x<length;x++){
		cout << customer_names[x] << "     " << savings[x] << "       " << checking[x] << "     " << endl;
	}

}

int Employee::View_payroll(){
	//uses private member username
	int length;
	int x = 0;
	int y = 0;
	string a;
	double b;
	string file_name = "payroll.txt";
	fstream fptr;
	fptr.open(file_name);
	if(!fptr.is_open()){
		cout << "could not open file" << endl;
	}
	cout << file_name << endl;
	fptr >> length;
	cout << length << endl;
	for(x=0;x<length;x++){

		fptr >> a;
		names.push_back(a);
		//cout << names[x] << endl;
		fptr >> b;
		payroll.push_back(b);
		//cout << payroll[x] << endl;
	}
	for(x=0;x<length;x++){
		if(names[x] == username){
			cout << "\nhello " << username << endl;
			cout << "your hourly rate is: $" << payroll[x] << endl;
			y = x;
			cout << endl;
		}
	}
	fptr.close();
	return 0;
}

int Employee::Employee_Menu(){
	cout << "Enter 1 to manage a customer account" << endl;
	cout << "Enter 2 to view payroll information" << endl;
	cout << "Enter 3 to add/remove customer account" << endl;
	cout << "Enter 4 to view all customer accounts" << endl;
	cout << "Enter 5 to exit menu" << endl;
	cin >> choice_e;
	return choice_e;
}

int Employee::Manage_Customer(string customer_name){

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
	cout << "length is" << length << endl;
	for(x=0;x<length;x++){
		fptr >> a;
		customer_names.push_back(a);
		fptr >> b;
	}
	fptr.close();

	for(x=0;x<length;x++){
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
	//cout << "length is" << length << endl;
	return 2;
}

int Employee::Employee_login(){
	int x = 0;
	int y = 0;
	string a;
	string b;
	int loop = 0;

	fstream fptr;
	fptr.open("employees.txt");
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
					//add or remove customer
				}
				if(choice_e == 4){
					//view all accounts
					employee1.View_All_Accounts();
				}
				if(choice_e == 5){
					//exit loop
					second_loop = 1;
				}
			}


		}
		if(choice == 3){
			cout << "we haven't written that yet" << endl;
		}
		if(choice == 4){
			cout << "we haven't written that yet" << endl;
		}
		if(choice == 5){
			cout << "thanks for using this random bank" << endl;
			return 3;
		}
	}
	return 0;
}















