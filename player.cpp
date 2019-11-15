// Section 003
// Monday, March 26, 2018
// Project 08 - Finding how much money and stock a player owns.

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
// Checks if a player can buy a stock.
bool Player::buy(Market &m, string stock, long date, long quantity)
{
	double price = m.get_price(stock, date);
	double cost = price * quantity;
	// Check if the price is -1.0.
	if (price != -1.0)
	{
		// Check if the cash is greater than the cost of the stock.
		if (cash >= cost)
		{
			// If so, update how much cash and how much stock the player has.
			cash = cash-cost;
			stocks[stock] = quantity;
			return true;
		}
		// If not, return false.
		else
		{
			return false;
		}
	}
	// If not, return false.
	else
	{
		return false;
	}
}
// Checks if a player can sell stock.
bool Player::sell(Market &m, string stock, long date, long quantity)
{
	map<string, long >::const_iterator itr = stocks.find(stock);
	double price = m.get_price(stock, date);
	double cost = price * quantity;
	// Check if the price is -1.0.
	if (price != -1.0)
	{
		// Check if the stock is owned.
		if (itr != stocks.end())
		{
			// Check if the quantity the player has is greater than the quantity inside the stock.
			if (itr->second >= quantity)
			{
				// If so, update how much cash the player has and the stock the player owns.
				cash = cash + cost;
				stocks[stock] = quantity;
				return true;
			}
			// If not, return false.
			else
			{
				return false;
			}
		}
		// If not, return false.
		else
		{
			return false;
		}
	}
	// If not, return false.
	else
	{
		return false;
	}
}
// Returns a string representation of the player.
string Player::to_str()
{
	map<string, long >::const_iterator itr;
	std::ostringstream os;
	// Output the cash the player has.
	os << fixed << setprecision(2) << cash;
	// Iterate through the stocks.
	for (itr = stocks.begin(); itr != stocks.end(); itr++)
	{
		// Output the symbol and the quantity.
		os << ',' << itr->first << ':' << itr->second;
	}
	// Return the player statistics.
	return os.str();
}

// Returns the combined total of two stocks.
Player Player::combine(Player &b)
{
	Player p(0);
	map<string, long >::const_iterator itr;
	// Combine the cash into a new player variable and reset the other totals to 0.
	p.cash = b.cash + this->cash;
	b.cash = 0;
	this->cash = 0;
	// Iterate through the stocks.
	for (itr = this->stocks.begin(); itr != this->stocks.end(); itr++)
	{
		// Add the stocks to the new player variable.
		p.stocks[itr->first] = itr->second;
	}
	// Iterate through the second player's stocks.
	for (itr = b.stocks.begin(); itr != b.stocks.end(); itr++)
	{
		// Add the stocks to the new player variable.
		p.stocks[itr->first] = itr->second;
	}
	// Return the total player stocks.
	return p;
}
