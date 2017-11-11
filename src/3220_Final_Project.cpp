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
	//cout << "creating savings account" << endl;
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
			cout << "hello " << username << endl;
			cout << "your balance is: $" << balance[x] << endl;
			y = x;
			cout << endl;
		}
	}
	fptr.close();
	int choice = 0;
	double amount;
	cout << "Enter 1 to add funds" << endl;
	cout << "Enter 2 to withdraw funds" << endl;
	cout << "Enter 3 to return to exit menu" << endl;
	cin >> choice;

	if(choice == 1){
		cout << "Enter amount you would like to deposit" << endl;
		cin >> amount;
		balance[y] = balance[y] + amount;
		cout << balance[y];
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
		cout << balance[y];
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
			cout << "welcome" << endl;
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
	cout << "Enter 1 to manage checking account" << endl;			//savings/checking?
	cout << "Enter 2 to manage savings account" << endl;
	cout << "Enter 3 to exit menu" << endl;
	cin >> choice_c;
	return choice_c;

}

int menu(){
	int choice = 0;
	cout << "Enter 1 to log in as a customer" << endl;		//create customer class
	cout << "Enter 2 to log in as an employee" << endl;		//employee class
	cout << "Enter 3 to log in as a manager" << endl;		//manager class
	cout << "Enter 4 to request new customer account" << endl;		//employee class
	cout << "Enter 5 to exit" << endl;
	cin >> choice;			//need to error check choice here
	return choice;
}

int main(void){
	int choice;
	int choice_c;
	int return_to_main = 0;
	int thing = 0;
	int second_loop = 0;
	string c = "checking.txt";
	string s = "savings.txt";
	string username;

	while(return_to_main == 0){

		choice = menu();

		if(choice == 1){
			Customer customer1;
			thing = customer1.Customer_login();
			//cout << "thing =" << thing << endl;
			username = customer1.get_username();
			//cout << "username is " << username << endl;
			if(thing == 1){
				continue;
			}
			//cout << "beginning of second loop" << endl;
			//cout << return_to_main << endl;
			second_loop = 0;
			while(second_loop == 0){
				//cout << "beginning of second loop" << endl;
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
		if(choice == 5){
			cout << "thanks for using this random bank" << endl;
			return 3;
		}
	}

	return 0;
}















