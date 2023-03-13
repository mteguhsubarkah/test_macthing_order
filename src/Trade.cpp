#include "../include/Trade.h"

Trade::Trade(std::string buy_order_id, std::string sell_order_id, double price, int quantity, int buy_socket, int sell_socket)
    : buy_order_id_(buy_order_id), sell_order_id_(sell_order_id), price_(price), quantity_(quantity), buy_socket_(buy_socket), sell_socket_(sell_socket)
{
}

std::string Trade::get_buy_order_id() const
{
    return buy_order_id_;
}

std::string Trade::get_sell_order_id() const
{
    return sell_order_id_;
}

double Trade::get_price() const
{
    return price_;
}

int Trade::get_quantity() const
{
    return quantity_;
}

int Trade::get_buy_socket() const
{
    return buy_socket_;
}

int Trade::get_sell_socket() const
{
    return sell_socket_;
}

std::string Trade::get_instrument() const
{
    // Assume that the instrument is the first 3 characters of the buy order ID
    return buy_order_id_.substr(0, 3);
}
