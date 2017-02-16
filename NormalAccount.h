#ifndef __NORMAL_ACCOUNT_H__
#define __NORMAL_ACCOUNT_H__

#include "Account.h"

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

#endif
