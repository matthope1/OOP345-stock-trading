#include <iostream>
#include <vector>
#include <map>
#include "portfolio.h"

using namespace std;

int main () { 

	// Portfolio myPortfolio;
	// int choice = 0;

	// while (true) {
	// 	cout << "====================================\n";
	// 	cout << "= Stock Portfolio Management System =\n";
	// 	cout << "====================================\n";

	// 	cout << "1. Add a Trade\n";
	// 	cout << "2. Print Trades\n";
	// 	cout << "3. Calculate Quantity of Shares\n";
	// 	cout << "4. Calculate Portfolio Value\n";
	// 	cout << "5. Exit\n";
	// 	cout << "Enter your choice: ";
	// 	cin >> choice;

	// 	switch (choice) {
	// 	case 1:
	// 		myPortfolio.addTrade();
	// 		break;
	// 	case 2:
	// 		myPortfolio.printTrades();
	// 		break;
	// 	case 3:
	// 		myPortfolio.calculateQtyShares();
	// 		break;
	// 	case 4:
	// 		myPortfolio.calculatePortfolioValue();
	// 		break;
	// 	case 5:
	// 		cout << "Exiting program." << endl;
	// 		return 0;
	// 	default:
	// 		cout << "Invalid choice. Please try again." << endl;
	// 	}
	// }

	// testing main
	cout << "main program" << endl;
	StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);
	StockTrade mySellTrade(2, "AAPL", "Sell", 100, 100.00);
	StockTrade myTrade2(3, "GOOG", "buy", 115, 175.00);
	StockTrade myTrade3(4, "GOOG", "buy", 222, 175.00);

	Portfolio myPortfolio;

	myPortfolio.addTradeNoValidate(myTrade);
	myPortfolio.addTradeNoValidate(mySellTrade);
	myPortfolio.addTradeNoValidate(myTrade);
	myPortfolio.addTradeNoValidate(myTrade);
	myPortfolio.addTradeNoValidate(myTrade2);
	myPortfolio.addTradeNoValidate(myTrade3);

	myPortfolio.printTrades();

	myPortfolio.calculateQtyShares();

	myPortfolio.calculatePortfolioValue();
	// end testing main

	return 0; 
}
