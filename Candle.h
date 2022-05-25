#ifndef CANDLE_H_
#define CANDLE_H_

#define RED     "\033[31m" //5
#define GREEN     "\033[32m" //5
#define RESET   "\033[0m" //7

#include <iostream>
#include <iomanip>

using namespace std;

class Candle
{
	int timestamp;
	float open, close, low, high;
public:
	Candle(int ts, float o, float c, float l, float h) :timestamp(ts), open(o), close(c), low(l), high(h) {}

	float getClose() { return close; }

	int getTs() { return timestamp; }

	friend ostream& operator<<(ostream& os, const Candle& c) {
		os<<((c.close > c.open) ? GREEN : RED) <<setw(11)<< c.timestamp << "  " << "Open: " << setw(7)<<left << c.open << " Close: " << setw(7)<<left << c.close << " Low: " << setw(7)<<left << c.low << " High: " << setw(7) <<left<< c.high<< RESET;
		return os;
	}
};

#endif
