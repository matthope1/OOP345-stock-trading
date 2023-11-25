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


StockTrade getUserInput(map<string, int> stockQty) {
	// passing in stockQty to check if there are enough shares to sell

	string symbol;
	string type;
	int numOfShares;
	double stockValue;

	// Get user input

	bool loop = true;

	bool tradeValid = false;

	cout << "Enter stock symbol (3-4 characters): ";
	while (!(cin >> symbol) || symbol.length() < 3 || symbol.length() > 4) {
		cout << "Invalid input. \nPlease enter a stock symbol of 3-4 characters: ";
		cin.clear();
	}

	// Convert stock symbol to uppercase
	for (char& c : symbol) {
		c = toupper(c);
	}



	//cout << "Enter stock symbol (3-4 characters): ";
	//while (!(cin >> symbol) || symbol.length() < 3 || symbol.length() > 4) {
	//	cout << "Invalid input. Please enter a stock symbol of 3-4 characters: ";
	//	cin.clear();
	//}

	//  resetting flag once out of previous loop 
	loop = true;

	while (loop) {
		cout << "Enter trade type (buy/sell): ";
		cin >> type;

		for (char& c : type) {
			c = toupper(c);
		}

		if (!(type == "BUY" || type == "SELL")) {
			cout << "Error: Trade type should be either 'buy' or 'sell'." << endl;
			// if the trade is in the portfolio already, then the sell should go through &
			// trade type is sell, check if there are enough shares to sell
		}
		else {
			loop = false;
		}
	}

	loop = true;

	while (loop) {
		cout << "Enter quantity of shares: ";
		cin >> numOfShares;

		if (numOfShares < 0) {
			cout << "Error: Quantity should be a positive integer." << endl;
		}
		else if (type == "SELL") {
			if ((stockQty.count(symbol) == 0) || stockQty[symbol] < numOfShares) {
				cout << "Error: Not enough shares to sell." << endl;
			}
			else {
				loop = false;
			}
		}
		else {
			loop = false;
		}
	}

	loop = true;

	while (loop) {
		cout << "Enter price per share: ";
		cin >> stockValue;

		if (stockValue < 0) {
			cout << "Error: Price should be a positive number." << endl;
		}
		else {
			loop = false;
		}
	}

	cout << endl;

	// if trade is a sell
	// check if trade exists in portfolio already
	// if it doesn't then the sell should fail
	// if it does, then check if thee are enough shares to sell

	// TODO: 



	StockTrade trade(0, symbol, type, numOfShares, stockValue);
	return trade;
}

