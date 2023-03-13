#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "order.h"
#include "trade.h"

class DataGenerator
{
public:
    DataGenerator();
    ~DataGenerator();
    std::vector<std::string> get_instruments() const;
    std::string generate_message(const std::string &instrument, double price, int quantity, bool is_buy) const;
    static std::unique_ptr<Order> parse_order_message(const std::string &message);
    static std::string generate_trade_message(const Trade &trade);

private:
    std::unordered_map<std::string, int> instrument_prices_;
};

#endif // DATA_GENERATOR_HPP
