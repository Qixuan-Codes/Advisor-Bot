#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <iostream>


// construct, reading a csv data file
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

// return vector of all known products in the dataset
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }

    // now flatten the map to a vector of strings
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

// return vector of Orders according to the sent filters
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}


double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    // comparing each price entry in the orderbookentry to get the highest price
    for (OrderBookEntry& e : orders)
    {
        if (e.price > max)max = e.price;
    }
    return max;
}


double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    // comparing each price entry in the orderbookentry to get the lowest price
    for (OrderBookEntry& e : orders)
    {
        if (e.price < min)min = e.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    // looping till next_timestamp is more than the timestamp in the parameter
    // if there isnt any timestamp greater it will wrap around the start
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    return next_timestamp;
}

double OrderBook::getTotalPrice(std::vector<OrderBookEntry>& orders)
{
    double total = 0;
    // looping all the orders based on the sent filters and adding all the prices together
    for (OrderBookEntry& e : orders)
    {
        total = total + e.price;
    }
    return total;
}

// return vector of all known timestamps in the dataset
std::vector<std::string> OrderBook::getKnownTimestamp()
{
    std::vector<std::string> timestamps;

    std::map<std::string, bool> timeMap;

    for (OrderBookEntry& e : orders)
    {
        timeMap[e.timestamp] = true;
    }

    // now flatten the map to a vector of strings
    for (auto const& e : timeMap)
    {
        timestamps.push_back(e.first);
    }

    return timestamps;
}

double OrderBook::getTotalAmount(std::vector<OrderBookEntry>& orders)
{
    double amount = 0;
    // looping all the orders based on the sent filters and adding all the amount together
    for (OrderBookEntry& e : orders)
    {
        amount = amount + e.amount;
    }
    return amount;
}

std::string OrderBook::getPreviousTime(std::string timestamp)
{
    std::string previous_timestamp = "";
    // previous_timestamp will keep updating till it is either more or equals to the timestamp in the 
    // parameter this will ensure previous timestamp will not just take the first value in the dataset
    // if there is no more previous timestamp it will return the first timestamp in the dataset
    for (OrderBookEntry& e : orders) {
        if (e.timestamp >= timestamp) {
            break;
        }
        else {
            previous_timestamp = e.timestamp;
        }
    }
    return previous_timestamp;
}