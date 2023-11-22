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
			StockTrade trade = getUserInput(stockQty);
			trade.tradeID = tradeIDCounter;
			trades.push_back(trade);
			tradeIDCounter++;
		}


		void printTrades() {
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
				double averagePrice;
				string symbol = entry.first;
				int totalShares = entry.second;
				double totalValue = stockValue[symbol];
				if (totalShares == 0) {
					averagePrice = 0;
				} else {
					averagePrice = totalValue / totalShares;
				}

				cout << "You have " << totalShares << " shares of " << symbol
					<< " purchased at an average price of $" << averagePrice << endl;
			}

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
