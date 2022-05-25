#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include <iostream>
#include <string>
#define CURL_STATICLIB
#include <curl/curl.h>
#include <map>
#include <regex>
#include <vector>
#include "Stock.h"



using namespace std;

class JSONParser
{
	string link;
	string s;
public:
	JSONParser(string s,long int from, long int to, string inter="1h") {
		link = "https://query1.finance.yahoo.com/v8/finance/chart/" + s + "?period1=" + to_string(from) + "&period2=" + to_string(to) + "&interval="+inter;
	}
	JSONParser(string l) :link(l) {}
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
	string curler(const char* lin);
	Stock parse();
};

#endif