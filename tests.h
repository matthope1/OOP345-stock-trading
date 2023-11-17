#include <iostream>
#include <vector>
#include <map>
#include "portfolio.h"


void test(int expected, int actual, string testName) {
	cout << testName << endl;

	if (expected == actual) {
		cout << "PASSED " << testName << endl;
	} else {
		cout << "FAILED " << testName << endl;
		cout << "Expected " << expected << " but got " << actual << endl;
	}

}


void testPortfolioAddTrade() {
	Portfolio myPortfolio;
	StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);

	test(0, myPortfolio.trades.size(), "testPortfolioAddTrade");
	myPortfolio.addTradeNoValidate(myTrade);
	test(1, myPortfolio.trades.size(), "testPortfolioAddTrade");

}