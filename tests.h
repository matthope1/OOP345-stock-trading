#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "portfolio.h"

// overloading << operator for map<string, int>
ostream& operator << (ostream& outputStream, const map<string, int>& map) {
	for (const auto& item : map) {
		outputStream << item.first << ": ";
		outputStream << item.second << " ";
	}

	return outputStream;
}

template <typename T>
void test(T expected, T actual, string testName) {
	cout << endl;
	cout << testName << endl;

	if (expected == actual) {
		cout << "PASSED " << testName << endl;
		cout << "Expected: " << expected << " == actual: " << actual << endl;
	}
	else {
		cout << "FAILED " << testName << endl;
		cout << "Expected: " << expected << " != actual:  " << actual << endl;
	}
	cout << endl;
}

void testPortfolioAddTrade() {
	Portfolio myPortfolio;
	StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);

	// there should be no trades in the portfolio 
	test<int>(0, myPortfolio.trades.size(), "testPortfolioAddTrade");
	myPortfolio.addTradeNoValidate(myTrade);
	// there should be one trade in the portfolio
	test<int>(1, myPortfolio.trades.size(), "testPortfolioAddTrade");
}


void testPortfolioCalculateQtyShares() {
	Portfolio myPortfolio;
	StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);
	StockTrade myTrade2(2, "AAPL", "buy", 200, 100.00);
	StockTrade myTrade3(3, "GOOG", "buy", 115, 175.00);
	StockTrade myTrade4(4, "GOOG", "buy", 222, 175.00);

	// create map of stock symbol and quantity of shares
	map<string, int> expectedResult;

	test<map<string, int>>(expectedResult, myPortfolio.calculateQtyShares(), "testPortfolioCalculateQtyShares");

	expectedResult["AAPL"] = 300;
	expectedResult["GOOG"] = 337;

	myPortfolio.addTradeNoValidate(myTrade);
	myPortfolio.addTradeNoValidate(myTrade2);
	myPortfolio.addTradeNoValidate(myTrade3);
	myPortfolio.addTradeNoValidate(myTrade4);

	test<map<string, int>>(expectedResult, myPortfolio.calculateQtyShares(), "testPortfolioCalculateQtyShares");
}

void testPortfolioValue() {
	Portfolio myPortfolio;

	StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);
	StockTrade myTrade2(2, "AAPL", "buy", 200, 100.00);
	StockTrade myTrade3(3, "GOOG", "buy", 115, 175.00);
	StockTrade myTrade4(4, "GOOG", "buy", 222, 175.00);

	// (100 * 100 ) + (200 * 100 ) + (115 * 175) + (222 * 175) = 88975

	myPortfolio.addTradeNoValidate(myTrade);
	myPortfolio.addTradeNoValidate(myTrade2);
	myPortfolio.addTradeNoValidate(myTrade3);
	myPortfolio.addTradeNoValidate(myTrade4);

	test<double>(88975, myPortfolio.calculatePortfolioValue(), "testPortfolioValue");
}