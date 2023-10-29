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
		// TODO: add tradeIDCounter to portfolio class
		// to keep track of trade id numbers

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
				cout << myTrades[i].tradeID  << " ";
				cout << myTrades[i].tradeType << " ";
				cout << myTrades[i].stockSymbol<< " ";
				cout << myTrades[i].quantity << " ";
				cout << myTrades[i].price << " " << endl;
			}
		}

		// to calculate the quantity of each stock in the portfolio
		// we can use a map, iterate through all the trades and add the quantity to the map with the stock symbol as the key
		map<string,int> calculateQtyShares() {
			map<string, int> stockQty;
			for (StockTrade trade: myTrades) {
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
		}

		void calculatePortfolioValue() {
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


int main () { 
	cout << "main program" << endl;
	StockTrade myTrade(1, "AAPL", "buy", 100, 100.00);
	StockTrade mySellTrade(1, "AAPL", "Sell", 100, 100.00);
  Portfolio myPortfolio;

	myPortfolio.addTrade(myTrade);
	myPortfolio.addTrade(myTrade);
	myPortfolio.addTrade(myTrade);
	myPortfolio.addTrade(mySellTrade);

	myPortfolio.printTrades();

	myPortfolio.calculateQtyShares();

	return 0; 
}
