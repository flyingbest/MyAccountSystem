#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

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

#endif

