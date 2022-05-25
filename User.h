#ifndef USER_H_
#define USER_H_

#include "Transaction.h"
#include "JSONParser.h"
#include <utility>
#include <map>
#include <time.h>
#include <algorithm>



#define RED     "\033[31m" //5
#define GREEN     "\033[32m" //5
#define RESET   "\033[0m" //7

class User
{
public:
	struct triple {
		float first=0;
		long int second=0;
		Stock* third = nullptr;

		triple() = default;
		triple(float f, long int s, Stock* th) :first(f), second(s), third(th) {}
	};
private:
	static map < string, triple > prices;
	vector<Transaction*> transactions;
	string Name;
	float balance;

public:
	User(string n, float b) :Name(n), balance(b) {}

	void updatePrice(string sym);
	float checkPrice(string sym);

	float getPrice(string sym) const;

	void buy(string sym, float amount);
	void sell(string sym, float amount);

	friend ostream& operator<<(ostream& os, const User& u);
};

#endif