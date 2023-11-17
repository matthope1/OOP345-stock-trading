#include <iostream>
#include <vector>
#include <map>

using namespace std;

class StockTrade {

	public:
		int tradeID;
		string stockSymbol;
		string tradeType;
		int quantity;
		double price;

		StockTrade(int tID, string symbol, string type, int numOfShares, double stockValue) {
			cout << "StockTrade constructor" << endl;
			tradeID = tID;
			stockSymbol = symbol;
			tradeType = type;
			quantity = numOfShares;
			price = stockValue;
		}
};

// portfolio class will store a vector of StockTrade objects
class Portfolio {
	public: 
		vector<StockTrade> trades;
		// TODO: add tradeIDCounter to portfolio class
		// to keep track of trade id numbers

		Portfolio() {
			cout << "Portfolio constructor" << endl;
		}

		void addTradeNoValidate(StockTrade trade) {
			trades.push_back(trade);
		}

		void addTrade() {
			// Declare variables for user input
			int tID;
			string symbol;
			string type;
			int numOfShares;
			double stockValue;

			// Get user input
			cout << "Enter trade ID: ";
			cin >> tID;
			cout << "Enter stock symbol (3-4 characters): ";
			cin >> symbol;
			cout << "Enter trade type (buy/sell): ";
			cin >> type;
			cout << "Enter quantity of shares: ";
			cin >> numOfShares;
			cout << "Enter price per share: ";
			cin >> stockValue;

			bool tradeValid = validateTradeInfo(tID, symbol, type, numOfShares, stockValue);

			if (tradeValid) {
				StockTrade trade(tID, symbol, type, numOfShares, stockValue);
				trades.push_back(trade);
			} else {
				cout << "Trade not added." << endl;
			}
		}

		void printTrades() {
			cout << "\n+----------------------------------+\n";
			cout << "|          List of Trades          |\n";
			cout << "+----------------------------------+\n";
			for (StockTrade trade: trades) {
				cout << trade.tradeID  << " ";
				cout << trade.tradeType << " ";
				cout << trade.stockSymbol<< " ";
				cout << trade.quantity << " ";
				cout << trade.price << " " << endl;
			}
			cout << "+----------------------------------+\n";
		}

		// to calculate the quantity of each stock in the portfolio
		// we can use a map, iterate through all the trades and add the quantity to the map with the stock symbol as the key
		map<string,int> calculateQtyShares() {
			cout << "\n+----------------------------------+\n";
			cout << "|    Quantity of Shares per Stock  |\n";
			cout << "+----------------------------------+\n";
			map<string, int> stockQty;
			for (StockTrade trade: trades) {
				// add quantity if the trade is a buy
				// subtract quantity if the trade is a sell 
				if (trade.tradeType == "buy") {
					stockQty[trade.stockSymbol] += trade.quantity;
				} else {
					stockQty[trade.stockSymbol] -= trade.quantity;
				}
			}
			for (auto& entry : stockQty) {
				cout << entry.first << " " << entry.second << " shares" << endl;
			}
			return stockQty;
			cout << "+----------------------------------+\n";
		}

		void calculatePortfolioValue() {
			cout << "\n\n+----------------------------------+\n";
			cout << "|      Current Portfolio Value     |\n";
			cout << "+----------------------------------+\n";
			map<string, int> stockShares;       // To store the total number of shares for each stock.
			map<string, double> stockValue;     // To store the total value of each stock.

			for (StockTrade& trade : trades) {
				if (trade.tradeType == "buy") {
					stockShares[trade.stockSymbol] += trade.quantity;
					stockValue[trade.stockSymbol] += trade.quantity * trade.price;
				}
				else if (trade.tradeType == "sell") {
					stockShares[trade.stockSymbol] -= trade.quantity;
					stockValue[trade.stockSymbol] -= trade.quantity * trade.price;
				}
			}

			for (auto& entry : stockShares) {
				string symbol = entry.first;
				int totalShares = entry.second;
				double totalValue = stockValue[symbol];

				cout << "You have " << totalShares << " shares of " << symbol
					<< " at a current value of $" << totalValue << endl;
			}
	}
};

bool validateTradeInfo(int tradeId, string stockSymbol, string tradeType, int quantity, double price) {
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

	return tradeValid;
}

// TODO: refer to workshopW9/IntBinaryTree.h and workshopW9/main.cpp to get an example of how to separate the class definition from the main program/ make header file

int main () { 

	Portfolio myPortfolio;
	int choice = 0;

	while (true) {
		cout << "====================================\n";
		cout << "= Stock Portfolio Management System =\n";
		cout << "====================================\n";

		cout << "1. Add a Trade\n";
		cout << "2. Print Trades\n";
		cout << "3. Calculate Quantity of Shares\n";
		cout << "4. Calculate Portfolio Value\n";
		cout << "5. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			myPortfolio.addTrade();
			break;
		case 2:
			myPortfolio.printTrades();
			break;
		case 3:
			myPortfolio.calculateQtyShares();
			break;
		case 4:
			myPortfolio.calculatePortfolioValue();
			break;
		case 5:
			cout << "Exiting program." << endl;
			return 0;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}

	// testing main
	// cout << "main program" << endl;
	// StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);
	// StockTrade mySellTrade(2, "AAPL", "Sell", 100, 100.00);
	// StockTrade myTrade2(3, "GOOG", "buy", 115, 175.00);
	// StockTrade myTrade3(4, "GOOG", "buy", 222, 175.00);

	// Portfolio myPortfolio;

	// myPortfolio.addTradeNoValidate(myTrade);
	// myPortfolio.addTradeNoValidate(mySellTrade);
	// myPortfolio.addTradeNoValidate(myTrade);
	// myPortfolio.addTradeNoValidate(myTrade);
	// myPortfolio.addTradeNoValidate(myTrade2);
	// myPortfolio.addTradeNoValidate(myTrade3);

	// myPortfolio.printTrades();

	// myPortfolio.calculateQtyShares();

	// myPortfolio.calculatePortfolioValue();
	// end testing main

	return 0; 
}
