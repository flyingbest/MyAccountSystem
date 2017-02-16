#include <iostream>
#include <cstring>		// Not using STL version.
using namespace std;

#define ACC_LEN 25
#define NAME_LEN 20
#define FIN_LEN 20

enum { OPEN=1, DEPOSIT, WITHDRAW, DISPLAY, EXIT };
enum { LEVEL_A=5, LEVEL_B=3, LEVEL_C=2 };
enum { NORMAL=1, CREDIT };

class Account{
private:
	char *acc_id;
	char *acc_holder;
	char *fin_ins_name;
	int balance;

public:
	Account(int money, char *id, char *name, char *fin_name);
	Account(const Account & ref);

	char* GetAccId() const;
	char* GetAccHolder() const;
	char* GetFinName() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void ShowCurInfo() const;
	~Account();
};

Account::Account(int money, char *id, char *name, char *fin_name) : balance(money){
	acc_id = new char[strlen(id)+1];
	strcpy(acc_id, id);
	acc_holder = new char[strlen(name)+1];
	strcpy(acc_holder, name);
	fin_ins_name = new char[strlen(fin_name)+1];
	strcpy(fin_ins_name, fin_name);
}
Account::Account(const Account & ref) : balance(ref.balance){
	acc_id = new char[strlen(ref.acc_id)+1];
	strcpy(acc_id, ref.acc_id);
	acc_holder = new char[strlen(ref.acc_holder)+1];
	strcpy(acc_holder, ref.acc_holder);
	fin_ins_name = new char[strlen(ref.fin_ins_name)+1];
	strcpy(fin_ins_name, ref.fin_ins_name);
}
char* Account::GetAccId() const{
	return acc_id;
}
char* Account::GetAccHolder() const{
	return acc_holder;
}
char* Account::GetFinName() const{
	return fin_ins_name;
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
	cout << "ID       : " << acc_id << endl;
	cout << "HOLDER   : " << acc_holder << endl;
	cout << "FIN_NAME : " << fin_ins_name << endl;
	cout << "BALANCE  : " << balance << endl;
	cout << "====================================" << endl;
}
Account::~Account(){
	delete []acc_id;
	delete []acc_holder;
	delete []fin_ins_name;
}

class NormalAccount : public Account{
private:
	int interRate;

public:
	NormalAccount(int money, char *id, char *name, char *fin_name, int rate) : Account(money, id, name, fin_name), interRate(rate){

	}
	virtual void Deposit(int money){
		Account::Deposit(money);
		Account::Deposit(money*(interRate/100.0));
	}
};

class HighCreditAccount : public NormalAccount{
private:
	int specialRate;

public:
	HighCreditAccount(int money, char *id, char *name, char *fin_name, int rate, int special) : NormalAccount(money, id, name, fin_name, rate), specialRate(special){

	}
	virtual void Deposit(int money){
		NormalAccount::Deposit(money);
		Account::Deposit(money*(specialRate/100.0));
	}
};

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

protected:
	void OpenNormalAccount();
	void OpenCreditAccount();
};

AccountControler::AccountControler() : ArrNum(0){

}

void AccountControler::DisplayMenu() const{
	cout << "+----------------------------------+" << endl;
	cout << "|               MENU               |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "|  1.  Open an new Account.        |" << endl;
	cout << "|  2.  Deposit money.              |" << endl;
	cout << "|  3.  Withdraw money.             |" << endl;
	cout << "|  4.  Display all account info.   |" << endl;
	cout << "|  5.  Exit the program.           |" << endl;
	cout << "+----------------------------------+" << endl;
}

void AccountControler::OpenAccount(){
	int sel;

	cout << "+----------------------------------+" << endl;
	cout << "|       Select Account Type        |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "|  1. Normal Account.              |" << endl;
	cout << "|  2. Credit Account.              |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "Select type(only number) : ";
	cin >> sel;

	if(sel == NORMAL){
		OpenNormalAccount();
	}else{
		OpenCreditAccount();
	}
}

void AccountControler::OpenNormalAccount(){
	char id[ACC_LEN];
	char name[NAME_LEN];
	char fin_name[FIN_LEN];
	int money;
	int interrate;

	cout << "+----------------------------------+" << endl;
	cout << "|      Opne an Normal Account      |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "Account ID     : ";
	cin >> id;
	cout << "Account HOLDER	: ";
	cin >> name;
	cout << "Fin_ins NAME   : ";
	cin >> fin_name;
	cout << "First Deposit Amount : ";
	cin >> money; 
	cout << "InterRate : ";
	cin >> interrate;
	cout << endl;

	for(int i=0; i<ArrNum; ++i){
		if(!strcmp(AccArr[i]->GetAccId(), id)){
			cout << "+----------------------------------+" << endl;
			cout << "|  [Account ID is already exist!]  |" << endl;
			cout << "+----------------------------------+" << endl << endl;
			return;
		}
	}
	
	AccArr[ArrNum++] = new NormalAccount(money, id, name, fin_name, interrate);
}

void AccountControler::OpenCreditAccount(){
	char id[ACC_LEN];
	char name[NAME_LEN];
	char fin_name[FIN_LEN];
	int money;
	int interrate;
	int creditLevel;

	cout << "+----------------------------------+" << endl;
	cout << "|      Opne an Credit Account      |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "Account ID     : ";
	cin >> id;
	cout << "Account HOLDER	: ";
	cin >> name;
	cout << "Fin_ins NAME   : ";
	cin >> fin_name;
	cout << "First Deposit Amount : ";
	cin >> money; 
	cout << "InterRate : ";
	cin >> interrate;
	cout << "Credit Level(1toA,2toB,3toC): ";
	cin >> creditLevel;
	cout << endl;

	for(int i=0; i<ArrNum; ++i){
		if(!strcmp(AccArr[i]->GetAccId(), id)){
			cout << "+----------------------------------+" << endl;
			cout << "|  [Account ID is already exist!]  |" << endl;
			cout << "+----------------------------------+" << endl << endl;
			return;
		}
	}
	
	switch(creditLevel){
		case 1:
			AccArr[ArrNum++] = new HighCreditAccount(money, id, name, fin_name, interrate, LEVEL_A);
			break;
		case 2:
			AccArr[ArrNum++] = new HighCreditAccount(money, id, name, fin_name, interrate, LEVEL_B);
			break;
		case 3:
			AccArr[ArrNum++] = new HighCreditAccount(money, id, name, fin_name, interrate, LEVEL_C);
			break;
		default:
			cout << "+----------------------------------+" << endl;
			cout << "|       Wrong Credit Number!       |" << endl;
			cout << "+----------------------------------+" << endl;
	}
}

void AccountControler::DepositMoney(){
	int money;
	char id[ACC_LEN];
	
	cout << "+----------------------------------+" << endl;
	cout << "|             DEPOSIT              |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "Account id : ";
	cin >> id;
	cout << "Amount     : ";
	cin >> money;

	for(int i=0; i<ArrNum; ++i){
		if(!strcmp(AccArr[i]->GetAccId(), id)){
			if(money <= 0){
				cout << "+----------------------------------+" << endl;
				cout << "|    Can not deposit below $0.     |" << endl;
				cout << "+----------------------------------+" << endl << endl;
				return;
			}else{	
				AccArr[i]->Deposit(money);
				cout << "+----------------------------------+" << endl;
				cout << "|        [Deposit Complete.]       |" << endl;
				cout << "+----------------------------------+" << endl << endl;
				return;
			}
		}
	}
	cout << "+----------------------------------+" << endl;
	cout << "|    [Account Id is not Valid!]    |" << endl;
	cout << "+----------------------------------+" << endl << endl;
}

void AccountControler::WithdrawMoney(){
	int money;
	char id[ACC_LEN];

	cout << "+----------------------------------+" << endl;
	cout << "|            WITHDRAW              |" << endl;
	cout << "+----------------------------------+" << endl;
	cout << "Account id : ";
	cin >> id;
	cout << "Amount     : ";
	cin >> money;
	
	for(int i=0; i<ArrNum; ++i){
		if(!strcmp(AccArr[i]->GetAccId(), id)){
			if(AccArr[i]->Withdraw(money) == 0){
				cout << "+----------------------------------+" << endl;
				cout << "|       [Not enough money!]        |" << endl;
				cout << "+----------------------------------+" << endl << endl;
				return;
			}
			cout << "+----------------------------------+" << endl;
			cout << "|       [Withdraw Complete.]       |" << endl;
			cout << "+----------------------------------+" << endl << endl;
			return;
		}
	}
	cout << "+----------------------------------+" << endl;
	cout << "|    [Account Id is not Valid!]    |" << endl;
	cout << "+----------------------------------+" << endl << endl;
}

void AccountControler::DisplayAccInfo() const{
	cout << "+----------------------------------+" << endl;
	cout << "|           ACCOUNT LIST           |" << endl;
	cout << "+----------------------------------+" << endl << endl;
	cout << "====================================" << endl;
	for(int i=0; i<ArrNum; ++i){
		cout << "No. " << i+1 << " Account Info." << endl;
		AccArr[i]->ShowCurInfo();
	}
	cout << "+----------------------------------+" << endl;
	cout << "|           END OF LIST            |" << endl;
	cout << "+----------------------------------+" << endl << endl;
}

AccountControler::~AccountControler(){
	for(int i=0; i<ArrNum; ++i){
		delete AccArr[i];
	}
}

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

