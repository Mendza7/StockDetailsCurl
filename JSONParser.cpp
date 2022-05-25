#include "JSONParser.h"


string JSONParser::curler(const char* lin)
{
	CURL* curl;
	CURLcode res;
	string readBuffer;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, lin);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return readBuffer;
}


Stock JSONParser::parse() {
	s = curler(link.c_str());


	string stockName;
	vector<int> timestamps;
	vector<float> open;
	vector<float> close;
	vector<float> high;
	vector<float> low;


	regex reg("(?=\"symbol\":\"(\\w*)\")");
	sregex_iterator currMatch(s.begin(), s.end(), reg);
	sregex_iterator lastMatch;

	while (currMatch != lastMatch) {
		smatch res = *currMatch;
		stockName = res.str(1);
		currMatch++;
	}
	//Dohvatanje timestamp-a
	reg = regex("(?=\"timestamp\":\\[([^\\]]*))");
	currMatch = sregex_iterator(s.begin(), s.end(), reg);
	smatch res = *currMatch;
	string ss = res.str(1);
	regex regnum("(\\d*),?");
	currMatch = sregex_iterator(ss.begin(), ss.end(), regnum);
	while (currMatch != lastMatch) {
		smatch res = *currMatch;
		string temp = res.str(1);
		if (temp.size())timestamps.push_back(stoi(temp));
		currMatch++;
	}

	//Dohvatanje open-a
	reg = regex("(?=\"open\":\\[([^\\]]*))");
	currMatch = sregex_iterator(s.begin(), s.end(), reg);
	res = *currMatch;
	ss = res.str(1);
	regnum = regex("(\\d*\\.\\d*)|(null),?");
	currMatch = sregex_iterator(ss.begin(), ss.end(), regnum);
	while (currMatch != lastMatch) {
		smatch res = *currMatch;
		string temp = res.str(1);
		if (res.str(0) == "null")timestamps.pop_back();
		else {
			if (temp.size())open.push_back(stod(temp));
		}
		currMatch++;
	}


	//Dohvatanje close-a
	reg = regex("(?=\"close\":\\[([^\\]]*))");
	currMatch = sregex_iterator(s.begin(), s.end(), reg);
	res = *currMatch;
	ss = res.str(1);
	regnum = regex("(\\d*\\.\\d*),?");
	currMatch = sregex_iterator(ss.begin(), ss.end(), regnum);
	while (currMatch != lastMatch) {
		smatch res = *currMatch;
		string temp = res.str(1);
		if (temp.size())close.push_back(stod(temp));
		currMatch++;
	}

	//Dohvatanje high-a
	reg = regex("(?=\"high\":\\[([^\\]]*))");
	currMatch = sregex_iterator(s.begin(), s.end(), reg);
	res = *currMatch;
	ss = res.str(1);
	regnum = regex("(\\d*\\.\\d*),?");
	currMatch = sregex_iterator(ss.begin(), ss.end(), regnum);
	while (currMatch != lastMatch) {
		smatch res = *currMatch;
		string temp = res.str(1);
		if (temp.size())high.push_back(stod(temp));
		currMatch++;
	}

	//Dohvatanje low-a
	reg = regex("(?=\"low\":\\[([^\\]]*))");
	currMatch = sregex_iterator(s.begin(), s.end(), reg);
	res = *currMatch;
	ss = res.str(1);
	regnum = regex("(\\d*\\.\\d*),?");
	currMatch = sregex_iterator(ss.begin(), ss.end(), regnum);
	while (currMatch != lastMatch) {
		smatch res = *currMatch;
		string temp = res.str(1);
		if (temp.size())low.push_back(stod(temp));
		currMatch++;
	}

	return Stock(stockName, timestamps, open, close, low, high);

}