#include <iostream>
#include <vector>
using namespace std;

int menu();
					//checking account - % bonus for deposit
					//savings account - normal deposit
class Account{
private:

protected:
	vector<int> FileContents;

public:
	void ViewBalance(int);
	Account();

};
class SavingsAccount:Account{
private:

protected:

public:

};
class CheckingAccount:Account{
private:

protected:

public:

};
class Customer{
private:
	int choice_c = 0;

public:
	Customer();
	int Customer_Menu();

};
Customer::Customer(){
	//enter username and password
	//open file to check
	//give option to return to main menu
}

int Customer::Customer_Menu(){
	cout << "Enter 1 to manage checking account" << endl;			//savings/checking?
	cout << "Enter 2 to manage savings account" << endl;
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
	choice = menu();
	cout << choice << endl;
	if(choice == 1){
		Customer customer1;
		choice_c = customer1.Customer_Menu();
		switch (choice_c){
		case 1:	//checking
			break;
		case 2: //savings funds
			break;

		}
	}

}
