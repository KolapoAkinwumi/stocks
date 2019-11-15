// Section 003
// March 26, 2018
// Organizes stock in the Dow Jones by date and price.

#include<iostream>
using std::cout; using std::endl;
#include<algorithm>
using std::copy;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;
#include<iomanip>
using std::boolalpha; using std::fixed; using std::setprecision;
#include <fstream>
using std::ifstream;
#include <map>
#include<cassert>

#include "proj08_market.h"
#include "proj08_player.h"

// Stores the prices of the stocks in a vector.
Market::Market(std::string s)
{
	long x;
	std::ifstream ifs(s);
	file_name = s;
	vector<double> v;
	// Iterate through the file;
	while (ifs >> x)
	{
		long date = x;
		// Iterate through the stock prices.
		for (int i = 0; i < 30; i++)
		{
			double y;
			ifs >> y;
			// Add the stocks to the vector.
			stocks[date].push_back(y);
		}
	}
}
// Returns the price of the stocks.
double Market::get_price(string stock, long date) const
{
	map<long, vector<double>>::const_iterator itr;
	int cnt = 0;
	// Find the date of the stock in the map.
	itr = stocks.find(date);
	// If the stock is found in the map, check if the stock is in the symbol list.
	if (itr != stocks.end())
	{
		vector<string>::const_iterator itr1 = std::find(symbol_list.begin(), symbol_list.end(), stock);
		// If so, get the index of the symbol, and return the stock price.
		if (itr1 != symbol_list.end())
		{
			long i = distance(symbol_list.begin(), itr1);
			return itr->second[i];
		}
	}
	return -1.0;
}
// Gets the highest and lowest stock prices.
pair<double, double> Market::high_low_year(long year, string symbol)
{
	pair<double, double> hl;
	map<long, vector<double>>::const_iterator itr;
	vector<double> v;
	// Iterate through the stocks.
	for (itr = stocks.begin(); itr != stocks.end(); itr++)
	{
		// Get the year.
		double itr1 = itr->first / 10000;
		if (year == itr1)
		{
			// Get the price, and add it to the vector.
			double gp = get_price(symbol, itr->first);
			v.push_back(gp);
			// If the price is -1.0, return error pair.
			if (gp == -1.0)
			{
				return { -1.0,-1.0 };
			}
		}
	}
	// Sort the vector.
	std::sort(v.begin(), v.end());
	// Add the highest and lowest stock prices to the vector.
	hl = std::make_pair(v.back(), v[0]);
	// Return the vector.
	return hl;
}

