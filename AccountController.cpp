#include "main.h"
#include "AccountController.h"
#include "Account.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"

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

