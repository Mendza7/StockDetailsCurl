#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "JSONParser.h"
#include "User.h"


#define RED     "\033[31m" //5
#define GREEN     "\033[32m" //5
#define RESET   "\033[0m" //7

using namespace std;

map <string,User::triple> User::prices;
int Transaction::TransactionID = 0;

int main_menu();

int main() {
	//string c = "https://query1.finance.yahoo.com/v8/finance/chart/tsla?period1=1617272670&period2=1617531870&interval=1d";
	/*string c = "https://query1.finance.yahoo.com/v8/finance/chart/aapl?period1=1616072670&period2=1617531870&interval=1h";
	JSONParser pars(c);
	Stock apl = pars.parse();
	Candle last_price=apl.last();
	cout << last_price << endl;
	cout << apl << endl;
	return 0;
	*/
	main_menu();
}



void korisnicki_meni(User* us) {
	bool flag = true;
	int k;
	Stock* stock = nullptr;
	while (flag) {
		cout << "MENI:" << endl << endl;
		cout << "1.Prikaz podataka o odredjenoj akciji." << endl;
		cout << "2.Racunanje indikatora za odredjenu akciju" << endl;
		cout << "3.Kupovina akcije." << endl;
		cout << "4.Prodaja akcije." << endl;
		cout << "5.Prikaz portfolija." << endl;
		cout << "6.Izlaz." << endl;




		cin >> k;
		switch (k)
		{
			system("cls");
		case 1:
		{
			system("cls");
			//parse
			long int from, to;
			string s;
			cout << "Unesite simbol akcije pracen sa 2 timestamp-a." << endl;

			cin >> s >> from >> to;
			if (from > to)break;
			JSONParser p("https://query1.finance.yahoo.com/v8/finance/chart/" + s + "?period1=" + to_string(from) + "&period2=" + to_string(to) + "&interval=1h");
			stock = new Stock(p.parse());
			cout << *stock << endl;

		}
		break;
		case 2:
		{
			if (!stock) break;
			cout << endl;
			int n;
			cout << "Unesite N: ";
			cin >> n;
			stock->setInfo();
			stock->EMA(n);
			stock->MA(n);
			cout << *stock << endl;

		}
		break;
		case 3:
		{
			string s;
			float am;
			cout << " Unesite simbol akcije: " << endl;
			cin >> s;
			cout << " Unesite kolicinu: " << endl;
			cin >> am;
			us->buy(s, am);

		}
		break;
		case 4:
		{	
			string s;
			float am;
			cout << " Unesite simbol akcije: " << endl;
			cin >> s;
			cout << " Unesite kolicinu: " << endl;
			cin >> am;
			us->sell(s, am);
		}
		break;
		case 5:
		{	
			cout << *us << endl;
		}
		break;
		case 6:
		{
			char c;
			system("cls");
			cout << "Da li ste sigurni da zelite da prekinete sa radom? (y/n)? " << endl;
			cin >> c;
			if (c == 'y' || c == 'Y') {
				flag = 0;
			}
		}
		break;
		break;
		system("cls");
		}

	}
}

void registration(string s)
{
	ofstream f;
	f.open(s, ios::app);
	string user;
	string pass;
	string balance;
	getchar();
	cout << "Username: ";
	getline(cin, user);
	cout << endl;
	if (user == "") {
		f << "default_user" << endl;
	}
	else {
		f << user << endl;
	}

	cout << "Password: ";
	getline(cin, pass);
	cout << endl;

	if (pass == "") {
		f << "default_pass" << endl;
	}
	else {
		f << pass << endl;
	}


	cout << "Balance: ";
	getline(cin, balance);
	cout << endl;

	if (balance == "") {
		f << 10000000 << endl;
	}
	else {
		f << balance << endl;
	}


	f.close();
	return;
}

User* login(string s)
{
	ifstream f;
	f.open(s);
	string user, pass;

	getchar();
	cout << "Username: ";
	getline(cin, user);
	cout << endl;

	cout << "Password: ";
	getline(cin, pass);
	cout << endl;

	string test;
	while (getline(f, test)) {
		if (test != user) {
			getline(f, test);
		}
		else {
			getline(f, test);
			if (test == pass) {
				string bal;
				getline(f, bal);
				float balance = stod(bal);
				cout << "login successful!" << endl;
				f.close();
				return new User(user,balance);
			}
		}
	}
	cout << "No username/pass found" << endl;
	f.close();
	return nullptr;
}

int main_menu() {
	int k;
	string users = "korisnici.txt";
	int flag = 1;

	while (flag) {
		cout << "MENI:" << endl << endl;
		cout << "1.Registracija korisnika" << endl;
		cout << "2.Login" << endl;
		cout << "3.Izlaz" << endl;

		cin >> k;
		switch (k)
		{
		case 1:
		{
			system("cls");
			registration(users);
		}
		break;
		case 2:
		{
			system("cls");
			User* user = login(users);
			if (!user)main_menu();
			else korisnicki_meni(user);
		}
		break;
		case 3:
		{
			char c;
			system("cls");
			cout << "Da li ste sigurni da zelite da prekinete sa radom? (y/n)? " << endl;
			cin >> c;
			if (c == 'y' || c == 'Y') {
				flag = 0;
			}
			
		}
		break;
		system("cls");
		}
	}
	return 0;
}

