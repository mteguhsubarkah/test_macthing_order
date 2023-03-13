#pragma once

#include <string>

class Trade
{
public:
    Trade(std::string buy_order_id, std::string sell_order_id, double price, int quantity, int buy_socket, int sell_socket);

    std::string get_buy_order_id() const;
    std::string get_sell_order_id() const;
    double get_price() const;
    int get_quantity() const;
    int get_buy_socket() const;
    int get_sell_socket() const;
    std::string get_instrument() const;

private:
    std::string buy_order_id_;
    std::string sell_order_id_;
    double price_;
    int quantity_;
    int buy_socket_;
    int sell_socket_;
};
