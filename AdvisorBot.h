#pragma once

#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <algorithm>


class AdvisorBot
{
public:
    AdvisorBot();
    // starter function
    void init();

private:
    // function to show the user what commands are there
    void help();

    // function to show how does each command work
    void helpCommand(std::string command);

    // function to show all available products
    void prod();

    // function to show the min ask/bid of the product chosen by the user
    void min(std::string product, std::string type);

    // function to show the max ask/bid of the product chosen by the user
    void max(std::string product, std::string type);

    // function to show the avg ask/bid of the product based on the amount of timesteps chosen by the user
    void avg(std::string product, std::string type, int timesteps);

    // function that predicts the min/max ask/bid of a specific product chosen by the user in the next time frame
    void predict(std::string s, std::string product, std::string type);

    // function that shows the current timestamp
    void time();

    // function to move to the next timestamp
    void step();

    // function to show information about a specific product chosen by the user
    void product(std::string product);

    // function to get the previous timestamp
    void back();

    // function to move further back
    void furtherBack(int amount);

    // function to move further forward
    void furtherForward(int amount);

    // function to move to the last timestamp
    void lastTimestamp();

    // function to calculate the standard deviation
    void standardDeviation(std::string product, std::string type);

    // function to read inputs from the command line
    std::string getUserCommand();

    // function to redirect command given by the user
    void processUserCommand(std::string input);

    // initialising currentTime as a string
    std::string currentTime;
    
    // selecting the csv file used
    OrderBook orderBook{ "20200601.csv" };

    // function to check whether the string is a number
    bool isDigit(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }
    
    std::string toUpper(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), toupper);
        return s;
    };

    std::string toLower(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), tolower);
        return s;
    };

};