#include "main.h"
#include "AccountController.h"

int main(int argc, char * argv[]){
	AccountControler manager;
	int selectNum;

	cout << "+----------------------------------+" << endl;
	cout << "|        MY ACCOUNT SYSTEM         |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "|            Made by Taeyoon Moon. |" << endl;
	cout << "|                  (Version 1.0.0) |" << endl;
	cout << "+----------------------------------+" << endl << endl;
	
	while(true){
		manager.DisplayMenu();
		cout << "Select Number(only number) : ";
		cin >> selectNum;
		cout << endl;

		switch(selectNum){
			case OPEN:
				manager.OpenAccount();
				break;
			case DEPOSIT:
				manager.DepositMoney();
				break;
			case WITHDRAW:
				manager.WithdrawMoney();
				break;
			case DISPLAY:
				manager.DisplayAccInfo();
				break;
			case EXIT:
				cout << "+---------------------------------------+" << endl;
				cout << "| Thank you for using! Have a nice day! |" << endl;
				cout << "+---------------------------------------+" << endl;
				return 0;
			default:
				cout << "+----------------------------------+" << endl;
				cout << "|   Wrong Number! select again!    |" << endl;
				cout << "+----------------------------------+" << endl;
			}
	}
	return 0;
}

