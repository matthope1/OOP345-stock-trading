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

	StockTrade() {
		cout << "StockTrade default constructor" << endl;
		tradeID = 0;
		stockSymbol = "";
		tradeType = "";
		quantity = 0;
		price = 0.0;
	}


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
	vector<StockTrade> myTrades;

	Portfolio() {
		cout << "Portfolio constructor" << endl;
	}

	void addTrade() {
		// TODO: add validation for the trade information
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

		// Validation checks
		// 1. stock symbol should be 3-4 characters
		if (symbol.length() < 3 || symbol.length() > 4) {
			cout << "Error: Stock symbol should be 3-4 characters long." << endl;
			return;
		}

		// 2. trade type should be a string, either buy or sell
		if (type != "buy" && type != "sell") {
			cout << "Error: Trade type should be either 'buy' or 'sell'." << endl;
			return;
		}

		// 3. quantity should be a positive integer
		if (numOfShares <= 0) {
			cout << "Error: Quantity should be a positive integer." << endl;
			return;
		}

		// 4. price should be a positive double
		if (stockValue <= 0.0) {
			cout << "Error: Price should be a positive number." << endl;
			return;
		}

		// 5. tradeID should be a positive integer
		if (tID <= 0) {
			cout << "Error: TradeID should be a positive integer." << endl;
			return;
		}

		// Creating the StockTrade object with user input
		StockTrade newTrade(tID, symbol, type, numOfShares, stockValue);

		// Adding trade to the portfolio
		myTrades.push_back(newTrade);
		cout << endl;
	}


	void printTrades() {
		cout << "\n+----------------------------------+\n";
		cout << "|          List of Trades          |\n";
		cout << "+----------------------------------+\n";
		for (int i = 0; i < myTrades.size(); i++) {
			cout << myTrades[i].tradeID << " ";
			cout << myTrades[i].tradeType << " ";
			cout << myTrades[i].quantity << " ";
			cout << myTrades[i].price << " " << endl;
		}
		cout << "+----------------------------------+\n";
	}

	// to calculate the quantity of each stock in the portfolio
	// we can use a map, iterate through all the trades and add the quantity to the map with the stock symbol as the key
	void calculateQtyShares() {
		cout << "\n+----------------------------------+\n";
		cout << "|    Quantity of Shares per Stock  |\n";
		cout << "+----------------------------------+\n";
		// TODO: this should return a mapping of stock symbols to quantity of shares
		map<string, int> stockQty;
		for (int i = 0; i < myTrades.size(); i++) {
			// TODO: add quantity if the trade is a buy
			//       subtract quantity if the trade is a sell 
			stockQty[myTrades[i].stockSymbol] += myTrades[i].quantity;
		}
		for (auto i = stockQty.begin(); i != stockQty.end(); i++) {
			cout << i->first << " " << i->second << " shares" << endl;
		}
		cout << "+----------------------------------+\n";
	}

	void calculatePortfolioValue() {
		cout << "\n\n+----------------------------------+\n";
		cout << "|      Current Portfolio Value     |\n";
		cout << "+----------------------------------+\n";
			map<string, int> stockShares;       // To store the total number of shares for each stock.
			map<string, double> stockValue;     // To store the total value of each stock.

			for (StockTrade& trade : myTrades) {
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


int main() {
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
	return 0;


}
