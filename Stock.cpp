#include "Stock.h"
#include "JSONParser.h"
#include <algorithm>

void Stock::MA(int n)
{
	MAs.clear();
	JSONParser p = JSONParser(name, candles[0]->getTs() - (7 * 24 * 3600 + n * 3600), candles[candles.size()-1]->getTs()+10);

	Stock data = p.parse();

	vector<Candle*>::iterator it = data.candles.begin();
	while ((*(it+1))->getTs() != candles[0]->getTs())it++;

	vector<Candle*>::iterator from = prev(it, n);
	for (;it!=data.candles.end(); it++,from++) {
		MAs.push_back(accumulate(from, it, 0, [](float a, Candle* b) {return a + b->getClose();}) / (float)n);
	}


}

void Stock::EMA(int n)
{
	EMAs.clear();
	JSONParser p = JSONParser(name, candles[0]->getTs() - (7 * 24 * 3600 + n * 3600), candles[candles.size()-1]->getTs()+10);

	Stock data = p.parse();

	vector<Candle*>::iterator it = data.candles.begin();
	int i = 0;
	while ((*(it+1))->getTs() != candles[0]->getTs()) it++;

	vector<Candle*>::iterator from = prev(it, n);

	for (; it != data.candles.end(); it++, from++) {
		EMAs.push_back(accumulate(from+1, it, (*from)->getClose(), [n](float a, Candle* b) {float m = 2.0 / (n * 1.0 + 1.0);  return ((1-m)* a + m * b->getClose()); }));
	}
	

	return;
}

float Stock::EMA_helper(int n,int i, Candle* c) {
	float m = 2.0 / (n * 1.0 + 1.0);

	return (m * c->getClose() + (1-m)*EMAs.back());
}
