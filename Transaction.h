#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include "Stock.h"
#include <iostream>
#include <iomanip>


class Transaction
{
public:
	enum type { BUY, SELL };

private:
	static int TransactionID;
	float amount;
	float price;
	Stock* stock;
	int id;
	type Ttype;

public:
	Transaction(float a, float p, Stock* s,type T) : amount(a), price(p), stock(s),Ttype(T) {
		id =TransactionID++;
	}
	Stock* getStock() { return stock; }
	float getAmount() { return amount; }
	float getPrice() { return price; }

	friend ostream& operator<<(ostream& os, const Transaction& t);
};

#endif
