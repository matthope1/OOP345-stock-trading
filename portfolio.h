#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "stockTrade.h"
#include <algorithm>
#include <iomanip>

using namespace std;

// portfolio class will store a vector of StockTrade objects
class Portfolio {
public:
	vector<StockTrade> trades;
	int tradeIDCounter = 1;

	Portfolio() {
		// cout << "Portfolio constructor" << endl;
	}

	void addTradeNoValidate(StockTrade trade) {
		trade.tradeID = tradeIDCounter;
		trades.push_back(trade);
		tradeIDCounter++;
	}

	void addTrade() {
		// Declare variables for user input
		int tID;
		string symbol;
		string type;
		int numOfShares;
		double stockValue;

		map<string, int> stockQty = calculateQtyShares();

		// Get user input
		cout << "\n+------------------------------------+\n";
		cout << "| Input Stock Trade Transaction Info |\n";
		cout << "+------------------------------------+\n";
		StockTrade trade = getUserInput(stockQty);
		trade.tradeID = tradeIDCounter;
		trades.push_back(trade);
		tradeIDCounter++;
	}


	void printTrades() {
		
		cout << "\n+---------------------------------------------------------+\n";
		cout << "|                      Print Trades                       |\n";
		cout << "+---------------------------------------------------------+\n";
		cout << "| Trade ID | Trade Type | Stock Symbol | Quantity | Price |\n";
		cout << "+---------------------------------------------------------+\n";
		for (StockTrade trade : trades) {
			cout << "| " << setw(9) << trade.tradeID << "| ";
			cout << setw(11) << trade.tradeType << "|  ";
			cout << setw(12) << trade.stockSymbol << "|    ";
			cout << setw(6) << trade.quantity << "| ";
			cout << setw(6) << fixed << setprecision(2) << trade.price << "|\n";
		}
		cout << "+---------------------------------------------------------+\n";
		cout << "\n\n";
	}

	// to calculate the quantity of each stock in the portfolio
	// we can use a map, iterate through all the trades and add the quantity to the map with the stock symbol as the key

	map<string, int> calculateQtyShares() {
		// Banner Header
		cout << "\n+----------------------------------+\n";
		cout << "|    Quantity of Shares per Stock  |\n";
		cout << "+----------------------------------+\n";

		// Column Headers
		const int symbolWidth = 17;
		const int sharesWidth = 12;
		cout << "| " << left << setw(symbolWidth) << "Stock Symbol"
			<< " | " << setw(sharesWidth) << "Shares"
			<< " |\n";
		cout << "+-------------------+--------------+\n";

		map<string, int> stockQty;
		for (StockTrade trade : trades) {
			if (trade.tradeType == "BUY") {
				stockQty[trade.stockSymbol] += trade.quantity;
			}
			else {
				stockQty[trade.stockSymbol] -= trade.quantity;
			}
		}

		// Print each stock's quantity
		for (auto& entry : stockQty) {
			cout << "| " << setw(symbolWidth) << entry.first
				<< " | " << setw(sharesWidth) << entry.second
				<< " |\n";
		}

		// Footer
		cout << "+-------------------+--------------+\n";
		cout << "\n\n";
		return stockQty;
	}


	double calculatePortfolioValue() {
		cout << "\n\n+----------------------------------+\n";
		cout << "|      Current Portfolio Value     |\n";
		cout << "+----------------------------------+\n";

		map<string, double> totalBuy, totalSell;
		double portfolioValue = 0;

		for (StockTrade& trade : trades) {
			if (trade.tradeType == "BUY") {
				totalBuy[trade.stockSymbol] += trade.quantity * trade.price;
				portfolioValue += trade.quantity * trade.price;
			}
			else if (trade.tradeType == "SELL") {
				totalSell[trade.stockSymbol] += trade.quantity * trade.price;
				portfolioValue -= trade.quantity * trade.price;
			}
		}

		for (auto& entry : totalBuy) {
			string symbol = entry.first;
			double buyAmount = entry.second;
			double sellAmount = totalSell[symbol];
			double profitLoss = sellAmount - buyAmount;

			cout << "Stock: " << symbol
				<< ", Profit/Loss: $" << profitLoss
				<< endl;
		}

		cout << endl  << "Total Portfolio Value:    $" << portfolioValue << endl << endl;

		return portfolioValue;
	}


	// TODO: function to calculate profit/loss for each position
	// if you buy apple stock today for $50, and tomorrow the stock is worth $52, your percentage gain is 4% ([$52 - $50] / $50).
	void calculateProfitLoss() {

		map<string, vector<StockTrade>> groupedTrades;

		// Group trades by stock symbol
		for (auto& trade : trades) {
			groupedTrades[trade.stockSymbol].push_back(trade);
		}

		// Iterate through each group
		for (auto& group : groupedTrades) {
			cout << "\nStock Symbol: " << group.first << endl;

			// Sort trades by tradeID
			sort(group.second.begin(), group.second.end(), [](const StockTrade& a, const StockTrade& b) {
				return a.tradeID < b.tradeID;
				});

			double lastPrice = 0;
			for (auto& trade : group.second) {
				if (lastPrice != 0) {
					double change = trade.price - lastPrice;
					double percentChange = (change / lastPrice) * 100;
					cout << "Trade ID: " << trade.tradeID << ", Change: " << change << ", Percent Change: " << percentChange << "%" << endl;
				}
				lastPrice = trade.price;
			}
		}
	}
};
