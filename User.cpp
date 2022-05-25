#include "User.h"



void User::updatePrice(string sym)
{
	time_t now = time(0);
	long int new_now = (long int)now;
	long int from = (long int)now - 3 * 86400;
	JSONParser p = JSONParser(sym, from, new_now,"15m");
	Stock* s = new Stock(p.parse());
	prices[sym] = triple(s->last().getClose(), new_now,s);
	return;
}

void User::buy(string sym, float amount)
{
	float price = checkPrice(sym);
	
	if ( price * amount > balance) {
		//greska
		cout << "Insufficient funds!" << endl;
		return;
	}

	transactions.push_back(new Transaction(amount, price, prices[sym].third,Transaction::BUY));
	balance = balance - price * amount;
	return;
}

void User::sell(string sym, float amount)
{
	float shares=0;
	for (auto i : transactions) {
		if (i->getStock()->getName() == sym)shares = shares + i->getAmount();
	}
	if (shares < amount) {
		//greska
		cout << "Nemate dovoljno akcija za datu prodaju." << endl;
		return;
	}
	
	float price = checkPrice(sym);

	transactions.push_back(new Transaction(amount, price, prices[sym].third, Transaction::SELL));
	balance = balance + price * amount;
}

float User::checkPrice(string sym)
{
	auto it = prices.find(sym);
	if (it != prices.end()) {
		time_t now = time(0);
		long int new_now = (long int)now;
		if ((it->second.second - new_now) > 10) {
			updatePrice(sym);
		}
	}
	else {
		updatePrice(sym);
	}

	return prices[sym].first;
}

float User::getPrice(string sym) const
{
	time_t now = time(0);
	long int new_now = (long int)now;
	long int from = (long int)now - 3 * 86400;
	JSONParser p = JSONParser(sym, from, new_now, "1h");
	Stock* s = new Stock(p.parse());
	return s->last().getClose();
}

ostream& operator<<(ostream& os,const User& u)
{

	auto prdiff = [u](Transaction* a2) {return u.getPrice(a2->getStock()->getName()) - a2->getPrice(); };
	os << "Korisnik: " << setw(20) << left << u.Name << " balans: " << setw(15) << left << fixed << setprecision(2) << u.balance << endl;
	for (auto i : u.transactions) {
		os << ((prdiff(i)>=0)? GREEN : RED) << *i << setw(7) << prdiff(i) << " " << setw(7) << prdiff(i) * 100 / i->getPrice()<< RESET << endl;
	}
	return os;
}
