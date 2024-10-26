# AdvisorBot

AdvisorBot is a command-line bot designed to help cryptocurrency investors analyze transaction data effectively. It loads transaction data from a CSV file and provides a variety of commands to aid investors in making informed decisions based on data analysis.

## Features

- **Command-Based Interface**: Users can input commands to interact with the bot and retrieve specific information.
- **Data Analysis Functions**: Includes functions to retrieve minimum, maximum, average values, predictions, timestamps, and standard deviations.
- **Time Navigation**: Move forward or backward in time to view historical or future transaction data.

## Commands

### Required Commands
- `Help`: Displays a list of all available commands.
- `Help <cmd>`: Shows details for a specific command.
- `Prod`: Lists all products available in the dataset.
- `Min <product> <order type>`: Finds the lowest price of a specified product.
- `Max <product> <order type>`: Finds the highest price of a specified product.
- `Avg <product> <order type> <timesteps>`: Calculates the average price over a number of timesteps.
- `Predict <min/max> <product> <order type>`: Predicts the max or min price in the next timestamp.
- `Time`: Displays the current timestamp.
- `Step`: Moves to the next timestamp.

### Custom Commands
- `Product <product>`: Provides detailed information about a specified product.
- `Back`: Moves one timestamp back.
- `Further Back <steps>`: Moves several timestamps back.
- `Further Forward <steps>`: Moves several timestamps forward.
- `Last Timestamp`: Moves to the last timestamp in the dataset.
- `Standard Deviation <product> <order type>`: Calculates the standard deviation for a product and order type.

## Installation

1. Clone the repository:
```
   git clone <repository-url>
```
2. Load your transaction data in a CSV format.
3. Run the program in Visual Studio or your preferred C++ environment.

## Usage

1. Launch the bot in your command line.
2. Use the commands listed above to interact with the bot and analyze cryptocurrency transaction data.

## Contributing

Feel free to contribute by submitting a pull request. All contributions are welcome!
