#pragma once
#include <iostream>

using namespace std;

class StockTrade {

	public:
		int tradeID;
		string stockSymbol;
		string tradeType;
		int quantity;
		double price;

		StockTrade(int tID, string symbol, string type, int numOfShares, double stockValue) {
			tradeID = tID;
			stockSymbol = symbol;
			tradeType = type;
			quantity = numOfShares;
			price = stockValue;
		}
};

bool validateTradeInfo(int tradeId, string stockSymbol, string tradeType, int quantity, double price, map<string,int> stockQty) {
	// 1. stock symbol should be 3-4 characters
	// 2. trade type should be a string, either buy or sell
	// 3. quantity should be a positive integer
	// 4. price should be a positive double
	// 5. tradeID should be a positive integer

	bool tradeValid = true;

	if (stockSymbol.length() < 3 || stockSymbol.length() > 4) {
		cout << "Error: Stock symbol should be 3-4 characters long." << endl;
		tradeValid = false;
	}

	if (tradeType != "buy" || tradeType != "sell") {
		cout << "Error: Trade type should be either 'buy' or 'sell'." << endl;
		tradeValid = false;
	}

	if (quantity < 0) {
		cout << "Error: Quantity should be a positive integer." << endl;
		tradeValid = false;
	}

	if (price < 0) {
		cout << "Error: Price should be a positive number." << endl;
		tradeValid = false;
	}
	
	if (tradeId < 0) {
		cout << "Error: TradeID should be a positive integer." << endl;
		tradeValid = false;
	}

	// if trade is a sell
	// check if trade exists in portfolio already
	// if it doesn't then the sell should fail
	// if it does, then check if thee are enough shares to sell
	if (tradeType == "sell") {
		if (stockQty[stockSymbol] < quantity) {
			cout << "Error: Not enough shares to sell." << endl;
			tradeValid = false;
		}
	}

	return tradeValid;
}