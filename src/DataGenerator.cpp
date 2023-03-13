#include "../include/DataGenerator.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

DataGenerator::DataGenerator()
{
    // Seed the random number generator
    srand(time(NULL));

    // Generate some initial prices for the instruments
    instrument_prices_["BBCA"] = 8800;
    instrument_prices_["BBRI"] = 4500;
    instrument_prices_["BBNI"] = 9000;
    instrument_prices_["BMRI"] = 9000;
}

DataGenerator::~DataGenerator()
{
    // Constructor
}

std::vector<std::string> DataGenerator::get_instruments() const
{
    std::vector<std::string> instruments;
    for (auto const &pair : instrument_prices_)
    {
        instruments.push_back(pair.first);
    }
    return instruments;
}

std::string DataGenerator::generate_message(const std::string &instrument, double price, int quantity, bool is_buy) const
{
    std::stringstream ss;
    ss << "TRADE|" << instrument << "|" << price << "|" << quantity << "|" << (is_buy ? "BUY" : "SELL");
    return ss.str();
}

std::unique_ptr<Order> DataGenerator::parse_order_message(const std::string &message)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(message);
    while (std::getline(ss, token, '|'))
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 4)
    {
        return nullptr;
    }

    auto order_type = (tokens[0] == "BUY") ? OrderType::Buy : OrderType::Sell;
    auto instrument = tokens[1];
    auto price = std::stod(tokens[2]);
    auto quantity = std::stoi(tokens[3]);

    return std::make_unique<Order>(order_type, instrument, price, quantity);
}

std::string DataGenerator::generate_trade_message(const Trade &trade)
{
    std::stringstream ss;
    ss << "TRADE|" << trade.get_instrument() << "|" << trade.get_price() << "|" << trade.get_quantity() << "|";
    if (trade.get_buy_socket() != -1)
    {
        ss << "BUYER|" << trade.get_buy_socket() << "|";
    }
    if (trade.get_sell_socket() != -1)
    {
        ss << "SELLER|" << trade.get_sell_socket() << "|";
    }
    return ss.str();
}
