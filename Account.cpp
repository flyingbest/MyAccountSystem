#include "main.h"
#include "Account.h"

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

