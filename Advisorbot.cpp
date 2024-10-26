#include "AdvisorBot.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <map>
#include <functional>


AdvisorBot::AdvisorBot()
{
    
}

void AdvisorBot::init()
{
    std::string input;

    // setting currentTime as the earliest time in the dataset provided
    currentTime = orderBook.getEarliestTime();

    std::cout << "Welcome to AdvisorBot, please enter your command or help for a list of commands." << std::endl;

    // this while loop is used to constantly check for commands in the command line
    while (true) {
        input = getUserCommand();
        processUserCommand(input);
    }
}

// this function was taken from the example code
std::string AdvisorBot::getUserCommand()
{
    std::string userOption;
    std::string line;

    // cin is used to read the commands from the command line and parsing it into a string which is then returned and used in processUserCommand()
    std::getline(std::cin, line);
    try {
        userOption = std::string(line);
    }
    catch (const std::exception& e) {

    }
    return userOption;
}

void AdvisorBot::processUserCommand(std::string input)
{
    std::vector<std::string> productList;
    std::vector<std::string> commandList = {"help","prod","min","max","avg","predict","time","step","product","back","last","std"};

    // getting all known products
    for (std::string& p : orderBook.getKnownProducts()) {
        // convert all strings to lowercase and pushing into productList
        productList.push_back(toLower(p));
    }

    // convert input to lowercase and tokenising it based on the space between characters
    std::vector<std::string> tokens = CSVReader::tokenise(toLower(input), ' ');

    // mapping strings to function
    std::map<std::string, std::function<void()>> commandMap = {
        {"help", std::bind(&AdvisorBot::help, this)},
        {"prod", std::bind(&AdvisorBot::prod, this)},
        {"time", std::bind(&AdvisorBot::time, this)},
        {"step", std::bind(&AdvisorBot::step, this)},
        {"back", std::bind(&AdvisorBot::back, this)},
        {"last", std::bind(&AdvisorBot::lastTimestamp, this)},
    };

    // redirect the user based on their command if no command is found output error message
    if (tokens.size() == 1) {
        // Check if the command is in the commandMap
        auto it = commandMap.find(tokens[0]);
        if (it != commandMap.end()) {
            // Call the member function using the std::function object stored in the map
            it->second();
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }

    else if (tokens.size() == 2) {
        if (tokens[0] == "help") {
            if (std::count(commandList.begin(), commandList.end(),tokens[1])) {
                helpCommand(tokens[1]);
            }
            else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        else if (tokens[0] == "product") {
            if (std::count(productList.begin(), productList.end(), tokens[1])) {
                product(toUpper(tokens[1]));
            }
            else {
                std::cout << "Invalid product" << std::endl;
            }
        }
        else if (tokens[0] == "back") {
            if (isDigit(tokens[1])) {
                furtherBack(stoi(tokens[1]));
            }
            else {
                std::cout << "Invalid timestep" << std::endl;
            }
        }
        else if (tokens[0] == "step") {
            if (isDigit(tokens[1])) {
                furtherForward(stoi(tokens[1]));
            }
            else {
                std::cout << "Invalid timestep" << std::endl;
            }
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }

    else if (tokens.size() == 3) {
        if (tokens[0] == "min") {
            if (std::count(productList.begin(), productList.end(), tokens[1])) {
                if (tokens[2] == "ask" || tokens[2] == "bid") {
                    min(toUpper(tokens[1]),tokens[2]);
                }
                else {
                    std::cout << "Invalid ask/bid command" << std::endl;
                }
            }
            else {
                std::cout << "Invalid product" << std::endl;
            }

        }
        else if (tokens[0] == "max") {
            if (std::count(productList.begin(), productList.end(), tokens[1])) {
                if (tokens[2] == "ask" || tokens[2] == "bid") {
                    max(toUpper(tokens[1]), tokens[2]);
                }
                else {
                    std::cout << "Invalid ask/bid command" << std::endl;
                }
            }
            else {
                std::cout << "Invalid product" << std::endl;
            }
        }
        else if (tokens[0] == "std") {
            if (std::count(productList.begin(), productList.end(), tokens[1])) {
                if (tokens[2] == "ask" || tokens[2] == "bid") {
                    standardDeviation(toUpper(tokens[1]), tokens[2]);
                }
                else {
                    std::cout << "Invalid ask/bid command" << std::endl;
                }
            }
            else {
                std::cout << "Invalid product" << std::endl;
            }
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }

    else if (tokens.size() == 4) {
        if (tokens[0] == "avg") {
            if (std::count(productList.begin(), productList.end(), tokens[1])) {
                if (tokens[2] == "ask" || tokens[2] == "bid") {
                    if (isDigit(tokens[3])) {
                        avg(toUpper(tokens[1]), tokens[2], stoi(tokens[3]));
                    }
                    else {
                        std::cout << "Invalid timestep" << std::endl;
                    }
                }
                else {
                    std::cout << "Invalid ask/bid command" << std::endl;
                }
            }
            else {
                std::cout << "Invalid product" << std::endl;
            }
        }
        else if (tokens[0] == "predict") {
            if (tokens[1] == "max" || tokens[1] == "min") {
                if (std::count(productList.begin(), productList.end(), tokens[2])) {
                    if (tokens[3] == "ask" || tokens[3] == "bid") {
                        predict(tokens[1], toUpper(tokens[2]), tokens[3]);
                    }
                    else {
                        std::cout << "Invalid ask/bid command" << std::endl;
                    }
                }
                else {
                    std::cout << "Invalid product" << std::endl;
                }
            }
            else {
                std::cout << "Invalid min/max command" << std::endl;
            }
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }
    else {
        std::cout << "Invalid command" << std::endl;
    }
}

void AdvisorBot::help()
{
    std::cout << "The available commands are help, help <cmd>, prod, min, max, avg, predict, time, step, product, back, last and std." << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::helpCommand(std::string command)
{
    std::map<std::string, std::string> commands = {
        {"help", "This command lists all available commands\nCommand: help"},
        {"prod", "This command lists available products\nCommand: prod"},
        {"min", "This command finds the minimum bid or ask for a product in the current timestamp\nCommand: min BTC/USDT ask/bid"},
        {"max", "This command finds the maximum bid or ask for a product in the current timestamp\nCommand: max BTC/USDT ask/bid"},
        {"avg", "This command computes the average ask or bid for the sent product over the sent number of timestamps\nCommand: avg BTC/USDT ask/bid 10"},
        {"predict", "This command predicts the max or min ask or bid for the sent product for the next timestamp\nCommand: predict max BTC/USDT ask/bid"},
        {"time", "This command states the current time in dataset\nCommand: time"},
        {"step", "This command moves to the next timestamp\nCommand: step\nThis command can also move further in time\nCommand: step 10"},
        {"product", "This command shows information about the product in the current timestamp\nCommand: product BTC/USDT"},
        {"back", "This command moves to the previous timestamp\nCommand: back\nThis command can also move further back in time\nCommand: back 10"},
        {"last", "This command moves to the last timestamp\nCommand: last"},
        {"std", "This command calculates the standard deviation of the ask/bid of the product in the current timestamp\nCommand: std BTC/USDT ask"}
    };
    std::cout << commands[command] << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::prod()
{
    std::string products;

    // getting all the known products in the dataset and appending it into a string
    for (std::string const& p : orderBook.getKnownProducts()) {
        products.append(p + ",");
    }

    // remove the last comma and printing it out
    products.pop_back();
    std::cout << "The available products are: " << products << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::min(std::string product, std::string type)
{
    std::cout << "Calculating the min " << type << " for " << product << std::endl;
    // getting the entries based on the product and type taken in by the parameter in the current timestamp 
    // and printing the minimum ask/bid for the product chosen
    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, currentTime);
    std::cout << "The min " << type << " for " << product << " is " << OrderBook::getLowPrice(entries) << " as of " << currentTime << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::max(std::string product, std::string type)
{
    std::cout << "Calculating the max " << type << " for " << product << std::endl;
    // getting the entries based on the product and type taken in by the parameter in the current timestamp
    // and printing the maximum ask/bid for the product chosen
    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, currentTime);
    std::cout << "The max " << type << " for " << product << " is " << OrderBook::getHighPrice(entries) << " as of " << currentTime << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::avg(std::string product, std::string type, int timesteps)
{
    int numberofProducts = 0;
    double totalPrice = 0;

    // setting the string timestamp as currentTime for the first loop
    std::string timestamp = currentTime;

    // function to return all the known timestamps in the dataset
    std::vector<std::string> timestamps = orderBook.getKnownTimestamp();
    
    // getting the index of the timestamp
    std::vector<std::string>::iterator itr = std::find(timestamps.begin(), timestamps.end(), timestamp);
    int index = std::distance(timestamps.begin(), itr);

    // if there is sufficient timestamps in the past print out the average
    // if not calculate all available past timestamp
    if (index >= timesteps - 1) {
        for (int i = 0; i < timesteps; i++) {
            // getting all the orders based on the type, product and timestamp and adding the number of products and total price
            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, timestamps[index]);
            numberofProducts += entries.size();
            totalPrice += OrderBook::getTotalPrice(entries);
            index -= 1;
        }
        // calculating the average
        double average = totalPrice / numberofProducts;
        std::cout << "Calculating the average" << std::endl;
        std::cout << "The average " << product << " ask price over the last " << timesteps << " timesteps is: " << average << std::endl;
        std::cout << "------------------------------------------------------------------------" << std::endl;
    }
    else {
        int index1 = index;
        for (int i = -1; i < index; i++) {
            // getting all the orders based on the type, product and timestamp and adding the number of products and total price
            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, timestamps[index1]);
            numberofProducts += entries.size();
            totalPrice += OrderBook::getTotalPrice(entries);
            index1 -= 1;
        }
        double average = totalPrice / numberofProducts;
        std::cout << "Unable to calculate the average for the past " << timesteps << " timesteps because there is not enough past timestamps" << std::endl;
        std::cout << "However, the average " << product << " ask price over the last " << index + 1 << " timesteps is: " << average << std::endl;
        std::cout << "------------------------------------------------------------------------" << std::endl;
    }
}

void AdvisorBot::predict(std::string m, std::string product, std::string type)
{
    std::cout << "Predicting the prices" << std::endl;

    double difference = 0;
    std::vector<double> prices;

    // setting the string timestamp as currentTime for the first loop
    std::string timestamp = currentTime;

    // function to return all the known timestamps in the dataset
    std::vector<std::string> timestamps = orderBook.getKnownTimestamp();

    std::vector<std::string>::iterator itr = std::find(timestamps.begin(), timestamps.end(), timestamp);
    int index = std::distance(timestamps.begin(), itr);


    // checking whether it is a min or max then looping all the previous timestamps to get either the highest or lowest price
    if (m == "min") {
        for (int i = 0; i <= index; i++) {
            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, timestamp);
            prices.push_back(OrderBook::getLowPrice(entries));
            timestamp = orderBook.getPreviousTime(timestamp);
        }
    }
    else {
        for (int j = 0; j <= index; j++) {
            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, timestamp);
            prices.push_back(OrderBook::getHighPrice(entries));
            timestamp = orderBook.getPreviousTime(timestamp);
        }
    }

    // if there is more than 1 price inside the vector calculate the difference between them
    if (prices.size() > 1) {
        for (int a = 1; a < prices.size(); a++) {
            difference += prices[a] - prices[a - 1];
        }
        // calculate the average difference between each highest or lowest and adding the difference
        // to the latest price to predict the next time frame and printing it out
        difference = difference / prices.size();
        double prediction = prices.back() + difference;
        std::cout << "The predicted " << m << " " << type << " for " << product << " is " << prediction << std::endl;
        std::cout << "------------------------------------------------------------------------" << std::endl;
    }
    else {
        std::cout << "Unable to make a prediction as there is only 1 timestamp" << std::endl;
        std::cout << "------------------------------------------------------------------------" << std::endl;
    }   
}

void AdvisorBot::time()
{
    // prints the current timestamp
    std::cout << "The current timestamp is: " << currentTime << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::step()
{
    // prints the next timestamp in the dataset
    currentTime = orderBook.getNextTime(currentTime);
    if (currentTime == "") {
        std::cout << "Error no more further timestamps" << std::endl;
        std::cout << "Wrapping back to the first timestamp" << std::endl;
        currentTime = orderBook.getEarliestTime();
    }
    std::cout << "Now at " << currentTime << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::back()
{
    // prints the next timestamp in the dataset
    std::string previousTime;
    previousTime = orderBook.getPreviousTime(currentTime);
    if (previousTime == "") {
        std::cout << "Error no earlier timestamp found" << std::endl;
        std::cout << "Now at " << orderBook.getEarliestTime() << std::endl;
        std::cout << "------------------------------------------------------------------------" << std::endl;
    }
    else {
        currentTime = previousTime;
        std::cout << "Now at " << currentTime << std::endl;
        std::cout << "------------------------------------------------------------------------" << std::endl;
    }
}

void AdvisorBot::product(std::string product)
{
    std::cout << "You have chosen " << product << std::endl;
    std::cout << "This is a summary of all the information as of " << currentTime << std::endl;

    // getting all the ask entries of the product in the current time and
    // printing the min,max bid, spread, number of entries and total amount in circulation 
    std::vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, product, currentTime);
    std::cout << "Number of entries found: " << askEntries.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(askEntries) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(askEntries) << std::endl;
    std::cout << "Spread " << OrderBook::getHighPrice(askEntries) - OrderBook::getLowPrice(askEntries) << std::endl;
    std::cout << "Amount in circulation: " << OrderBook::getTotalAmount(askEntries) << std::endl;

    // getting all the bid entries of the product in the current time and
    // printing the min,max bid, spread, number of entries and total amount in circulation 
    std::vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, product, currentTime);
    std::cout << "Number of entries found: " << bidEntries.size() << std::endl;
    std::cout << "Max bid: " << OrderBook::getHighPrice(bidEntries) << std::endl;
    std::cout << "Min bid: " << OrderBook::getLowPrice(bidEntries) << std::endl;
    std::cout << "Spread " << OrderBook::getHighPrice(bidEntries) - OrderBook::getLowPrice(bidEntries) << std::endl;
    std::cout << "Amount in circulation: " << OrderBook::getTotalAmount(bidEntries) << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::furtherBack(int amount) {
    for (int i = 0; i < amount; i++) {
        if (currentTime == orderBook.getEarliestTime()) {
            std::cout << "Error no earlier timestamp found" << std::endl;
            break;
        }
        else {
            currentTime = orderBook.getPreviousTime(currentTime);
        }   
    } 
    std::cout << "now at " << currentTime << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::furtherForward(int amount) {
    for (int i = 0; i < amount; i++) {
        if (currentTime == "") {
            std::cout << "Error no more further timestamps" << std::endl;
            std::cout << "Wrapping back to the first timestamp" << std::endl;
            currentTime = orderBook.getEarliestTime();
            break;
        }
        else {
            currentTime = orderBook.getNextTime(currentTime);
        } 
    }
    std::cout << "now at " << currentTime << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::lastTimestamp() {
    std::vector<std::string> timestamps = orderBook.getKnownTimestamp();
    currentTime = timestamps.back();
    std::cout << "now at " << currentTime << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void AdvisorBot::standardDeviation(std::string product, std::string type) {
    std::cout << "You have chosen " << product << std::endl;
    double variance = 0;
    // getting the orderbook entries based on the order type, product and current time
    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, currentTime);
    double sum = orderBook.getTotalPrice(entries);
    double mean = sum / entries.size();
    for (int i = 0; i < entries.size(); i++) {
        variance += pow(entries[i].price - mean, 2);
    };
    float standardDeviation = sqrt(variance/entries.size());
    std::cout << "The Standard Deviation for the " << product << " " << type << " entries is: " << standardDeviation << std::endl;
}