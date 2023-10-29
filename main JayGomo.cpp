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
	vector<StockTrade> myTrades;

	Portfolio() {
		cout << "Portfolio constructor" << endl;
	}

	void addTrade(StockTrade trade) {
		// TODO: add validation for the trade information   
		// 1. stock symbol should be 3-4 characters
		// 2. trade type should be a string, either buy or sell
		// 3. quantity should be a positive integer
		// 4. price should be a positive double
		// 5. tradeID should be a positive integer

		myTrades.push_back(trade);
	}

	void printTrades() {
		for (int i = 0; i < myTrades.size(); i++) {
			cout << myTrades[i].tradeID << " ";
			cout << myTrades[i].tradeType << " ";
			cout << myTrades[i].quantity << " ";
			cout << myTrades[i].price << " " << endl;
		}
	}

	// to calculate the quantity of each stock in the portfolio
	// we can use a map, iterate through all the trades and add the quantity to the map with the stock symbol as the key
	void calculateQtyShares() {
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
	}

	void calculatePortfolioValue() {
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
		




		// TODO: 
		// create new map for storing stockSymbol -> totalStockValue 
		// iterate through the trades and 
		// subtract from total stock val for buy trades
		// add to total stock val for sell trades
		// do the opposite for the the amount of stocks
		// add stock quantity for buy trades 
		// subtract from quantity for sell trades
	}
};


int main() {
	cout << "main program" << endl;
	StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);
	StockTrade myTrade2(2, "GOOG", "buy", 115, 175.00);
	StockTrade myTrade3(3, "GOOG", "buy", 222, 175.00);

	Portfolio myPortfolio;

	myPortfolio.addTrade(myTrade);
	myPortfolio.addTrade(myTrade);
	myPortfolio.addTrade(myTrade);
	myPortfolio.addTrade(myTrade2);
	myPortfolio.addTrade(myTrade3);

	myPortfolio.printTrades();

	myPortfolio.calculateQtyShares();

	myPortfolio.calculatePortfolioValue();

	return 0;
}
