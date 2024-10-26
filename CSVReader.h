#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

// this file was taken from the example code
class CSVReader
{
public:
    CSVReader();

    // function that gets the CSV file location/name and reads its content
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    // function that tokenise the file based on its separator
    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    // function that converts 
    static OrderBookEntry stringsToOBE(std::string price, std::string amount, std::string timestamp, std::string product, OrderBookType OrderBookType);

private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};