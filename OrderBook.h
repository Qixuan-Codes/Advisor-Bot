#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
public:
    // construct, reading a csv data file, taken from example code
    OrderBook(std::string filename);
    // return vector of all known products in the dataset, taken from example code
    std::vector<std::string> getKnownProducts();
    // return vector of Orders according to the sent filters, taken from example code
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    // returns the earliest time in the orderbook, taken from example code
    std::string getEarliestTime();
    // returns the next timestamp after the sent time in the orderbook
    // if there is no next timestamp taken from example code
    std::string getNextTime(std::string timestamp);
    // returns the highest price in the dataset based on the sent filters, taken from example code
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    // returns the lowest price in the dataset based on the sent filters, taken from example code
    static double getLowPrice(std::vector<OrderBookEntry>& orders);

    // return a vector of all known timestamps in the dataset
    std::vector<std::string> getKnownTimestamp();
    // returns the total price based on the sent filters
    static double getTotalPrice(std::vector<OrderBookEntry>& orders);
    // returns the total amount based on the sent filters
    static double getTotalAmount(std::vector<OrderBookEntry>& orders);
    // returns the timestamp before the sent timestamp in the orderbook
    std::string getPreviousTime(std::string timestamp);

private:
    std::vector<OrderBookEntry> orders;
};
