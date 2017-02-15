#include <iostream>
#include <cstring>		// Not using STL.
using namespace std;

#define ACC_LEN 25
#define NAME_LEN 20

enum { OPEN=1, DEPOSIT, WITHDRAW, DISPLAY, EXIT };

class Account{
private:
	char *acc_id;
	char *acc_holder;
	int balance;

public:
	Account(int money, char *id, char *name);
	Account(const Account & ref);

	char* GetAccId() const;
	char* GetAccHolder() const;
	void Deposit(int money);
	int Withdraw(int money);
	void ShowCurInfo() const;
	~Account();
};

Account::Account(int money, char *id, char *name) : balance(money){
	acc_id = new char[strlen(id)+1];
	strcpy(acc_id, id);
	acc_holder = new char[strlen(name)+1];
	strcpy(acc_holder, name);
}
Account::Account(const Account & ref) : balance(ref.balance){
	acc_id = new char[strlen(ref.acc_id)+1];
	strcpy(acc_id, ref.acc_id);
	acc_holder = new char[strlen(ref.acc_holder)+1];
	strcpy(acc_holder, ref.acc_holder);
}
char* Account::GetAccId() const{
	return acc_id;
}
char* Account::GetAccHolder() const{
	return acc_holder;
}
void Account::Deposit(int money){
	balance += money;
}
int Account::Withdraw(int money){
	if(balance < money){
		return 0;
	}
	balance -= money;
	return money;
}
void Account::ShowCurInfo() const{
	cout << "Account ID : " << acc_id << endl;
	cout << "Account HOLDER : " << acc_holder << endl;
	cout << "Cur Balance : " << balance << endl;
}
Account::~Account(){
	delete []acc_id;
	delete []acc_holder;
}

class AccountControler{
private:
	Account * AccArr[100];
	int ArrNum;

public:
	AccountControler();
	void DisplayMenu() const;
	void OpenAccount();
	void DepositMoney();
	void WithdrawMoney();
	void DisplayAccInfo() const;
	~AccountControler();
};

AccountControler::AccountControler() : ArrNum(0){

}

void AccountControler::DisplayMenu() const{
	cout << "----------Menu----------" << endl;
	cout << "1. Open an new Account. " << endl;
	cout << "2. Deposit money. " << endl;
	cout << "3. Withdraw money. " << endl;
	cout << "4. Display all account info. " << endl;
	cout << "5. Exit the program. " << endl;
}

void AccountControler::OpenAccount(){
	char id[ACC_LEN];
	char name[NAME_LEN];
	int money;

	cout << "|| Open an Account ||" << endl;
	cout << "Account ID : ";
	cin >> id;
	cout << "Account HOLDER : ";
	cin >> name;
	cout << "Deposit Amount : ";
	cin >> money; 
	cout << endl;

	for(int i=0; i<ArrNum; ++i){
		if(!strcmp(AccArr[i]->GetAccId(), id)){
			cout << "Account ID is already exist!" << endl << endl;
			return;
		}
	}
	
	AccArr[ArrNum++] = new Account(money, id, name);
}

void AccountControler::DepositMoney(){
	int money;
	char id[ACC_LEN];
	
	cout << "|| DEPOSIT ||" << endl;
	cout << "Account id : ";
	cin >> id;
	cout << "Deposit Amount : ";
	cin >> money;

	for(int i=0; i<ArrNum; ++i){
		if(!strcmp(AccArr[i]->GetAccId(), id)){
			AccArr[i]->Deposit(money);
			cout << "Deposit Complete." << endl << endl;
			return;
		}
	}
	cout << "Account Id is not Valid!" << endl << endl;
}

void AccountControler::WithdrawMoney(){
	int money;
	char id[ACC_LEN];

	cout << "|| WITHDRAW ||" << endl;
	cout << "Account id : ";
	cin >> id;
	cout << "Withdraw Amount : ";
	cin >> money;
	
	for(int i=0; i<ArrNum; ++i){
		if(!strcmp(AccArr[i]->GetAccId(), id)){
			if(AccArr[i]->Withdraw(money) == 0){
				cout << "Not enough money!" << endl << endl;
				return;
			}
			cout << "Withdraw Complete." << endl << endl;
			return;
		}
	}
	cout << "Account Id is not Valid!" << endl << endl;
}

void AccountControler::DisplayAccInfo() const{
	for(int i=0; i<ArrNum; ++i){
		AccArr[i]->ShowCurInfo();
		cout << endl;
	}
}

AccountControler::~AccountControler(){
	for(int i=0; i<ArrNum; ++i){
		delete AccArr[i];
	}
}

int main(int argc, char * argv[]){
	AccountControler manager;
	int selectNum;
	
	while(1){
		manager.DisplayMenu();
		cout << "select number : ";
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
				cout << "Thank you for using. Have a nice day!" << endl;
				return 0;
			default:
				cout << "Illegal selection! enter again.." << endl;
				break;
			}
	}
	return 0;
}

