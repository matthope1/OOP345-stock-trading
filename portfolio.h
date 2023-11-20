#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "stockTrade.h"

using namespace std;

// portfolio class will store a vector of StockTrade objects
class Portfolio {
	public: 
		vector<StockTrade> trades;
		// TODO: add tradeIDCounter to portfolio class
		// to keep track of trade id numbers

		Portfolio() {
			// cout << "Portfolio constructor" << endl;
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

		double calculatePortfolioValue() {
			cout << "\n\n+----------------------------------+\n";
			cout << "|      Current Portfolio Value     |\n";
			cout << "+----------------------------------+\n";
			map<string, int> stockShares;       // To store the total number of shares for each stock.
			map<string, double> stockValue;     // To store the total value of each stock.
			double portfolioValue = 0; 

			for (StockTrade& trade : trades) {
				if (trade.tradeType == "buy") {
					stockShares[trade.stockSymbol] += trade.quantity;
					stockValue[trade.stockSymbol] += trade.quantity * trade.price;
					portfolioValue += trade.quantity * trade.price;
				}
				else if (trade.tradeType == "sell") {
					stockShares[trade.stockSymbol] -= trade.quantity;
					stockValue[trade.stockSymbol] -= trade.quantity * trade.price;
					portfolioValue -= trade.quantity * trade.price;
				}
			}

			for (auto& entry : stockShares) {
				string symbol = entry.first;
				int totalShares = entry.second;
				double totalValue = stockValue[symbol];
				double averagePrice = totalValue / totalShares;

				cout << "You have " << totalShares << " shares of " << symbol
					<< " purchased at an average price of $" << averagePrice << endl;
			}

			return portfolioValue;
		}
		// TODO: function to calculate profit/loss for each position
		


};


