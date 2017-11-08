#include <iostream>
#include <vector>
using namespace std;

int menu();

class Customer{
private:
	int choice = 0;

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
	cout << "Enter 1 to view account balance" << endl;			//savings/checking?
	cout << "Enter 2 to deposit funds" << endl;
	cout << "Enter 3 to withdraw funds" << endl;
	return 1;
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
	choice = menu();
	cout << choice << endl;
	if(choice == 1){
		Customer customer1;
		customer1.Customer_Menu();
	}

}
