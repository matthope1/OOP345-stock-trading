#include <iostream>
#include <vector>
#include <map>
#include "portfolio.h"


template <typename T>
void test(T expected, T actual, string testName) {
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

	// there should be no trades in the portfolio 
	test<int>(0, myPortfolio.trades.size(), "testPortfolioAddTrade");
	myPortfolio.addTradeNoValidate(myTrade);
	// there should be one trade in the portfolio
	test<int>(1, myPortfolio.trades.size(), "testPortfolioAddTrade");

}