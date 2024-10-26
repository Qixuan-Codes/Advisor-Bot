#include "CSVReader.h"
#include <iostream>
#include <fstream>

// this file was taken from the example code
CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;
    // imports the csv file 
    std::ifstream csvFile{ csvFilename };
    std::string line;
    // checking if it has successfully been opened
    if (csvFile.is_open())
    {
        // getting each line in the csv file
        while (std::getline(csvFile, line))
        {
            try {
                // tokenising the entries and pushing it into entries
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            // catch any errors that occurred when tokenising each line and printing an error
            catch (const std::exception& e)
            {
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }
        }// end of while
    }

    // output how many lines were successfully read in the csvFile
    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    // finding the first string that is not the separator starting from the first character in the data provided
    // and assigning it to start
    start = csvLine.find_first_not_of(separator, 0);
    do {
        // finding the last string that is not the separator starting from start
        end = csvLine.find_first_of(separator, start);
        // break if it is empty
        if (start == csvLine.length() || start == end) break;
        // if it is not empty 
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    // checking if there is 5 tokens in the data provided since there are 5 tokens in each line in the csv file
    // if there isnt output an error message and throw an exception
    if (tokens.size() != 5)
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    // changing the third and fourth token from string to double
    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception& e) {
        std::cout << "CSVReader::stringsToOBE bad price float! " << tokens[3] << std::endl;
        std::cout << "CSVReader::stringsToOBE bad amount float! " << tokens[4] << std::endl;
        throw;
    }
    // enter the data collected into an orderbookentry
    OrderBookEntry obe{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}


OrderBookEntry CSVReader::stringsToOBE(std::string priceString, std::string amountString, std::string timestamp, std::string product, OrderBookType orderType)
{
    double price, amount;
    // changing the price and amount from string to double and throw an exception if it cant be converted
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception& e) {
        std::cout << "CSVReader::stringsToOBE bad price float! " << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE bad amount float! " << amountString << std::endl;
        throw;
    }
    // enter the data collected into an orderbookentry
    OrderBookEntry obe{price, amount, timestamp, product, orderType};
    return obe;
}
