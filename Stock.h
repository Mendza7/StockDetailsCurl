#ifndef STOCK_H_
#define STOCK_H_

#include <vector>
#include <numeric>
#include "Candle.h"
#include <iomanip>


using namespace std;

class Stock
{
	string name;
	vector<Candle*> candles;
	vector<float> MAs;
	vector<float> EMAs;
	bool advanced_info;
public:
	Stock(string sn,vector<int> ts, vector<float> o, vector<float> c, vector<float> l, vector<float> h,bool adv_info=false):name(sn),advanced_info(adv_info) {
		for (int i = 0; i < o.size(); i++) {
			candles.push_back(new Candle(ts[i], o[i], c[i], l[i], h[i]));
		}
	}

	Candle last() {
		return *candles[candles.size() - 1];
	}

	inline void setInfo() { advanced_info = true; }

	inline string getName() { return name; }

	void MA(int n);

	void EMA(int n);

	float EMA_helper(int n,int i,Candle* c);

	ostream& pisi_osnovno(ostream& os) const {
		for (auto i : candles) {
			os << *i << endl;
		}
		return os;
	}

	ostream& pisi_advanced(ostream& os) const {
		for (int i = 0; i < candles.size(); i++) {
			os << *candles[i] << " " << setw(8)<<left <<MAs[i] << " " << setw(8) <<left << EMAs[i] << endl;
		}
		return os;
	}
	
	friend ostream& operator<<(ostream& os, const Stock& s) {
		if (s.advanced_info) return s.pisi_advanced(os);
		else return s.pisi_osnovno(os);
	}
};

#endif