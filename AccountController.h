#ifndef __ACCOUNT_CONTROLLER_H__
#define __ACCOUNT_CONTROLLER_H__

#include "Account.h"

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

#endif

