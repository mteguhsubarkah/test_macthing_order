#pragma once

#include <string>

enum class OrderType
{
    Buy,
    Sell
};

class Order
{
public:
    Order(int id, std::string symbol, double price, int quantity, OrderType type, std::string client_id);
    int get_id() const;
    std::string get_symbol() const;
    double get_price() const;
    int get_quantity() const;
    OrderType get_type() const;
    std::string get_client_id() const;
    void reduce_quantity(int quantity);

    void set_id(const std::string &id_str);

    void set_quantity(int quantity) { quantity_ = quantity; }
    void set_client_id(const std::string &client_id);

private:
    int id_;
    std::string symbol_;
    double price_;
    int quantity_;
    OrderType type_;
    std::string client_id_;
};

// Implementation of Order class

Order::Order(int id, std::string symbol, double price, int quantity, OrderType type, std::string client_id)
    : id_(id), symbol_(std::move(symbol)), price_(price), quantity_(quantity), type_(type), client_id_(std::move(client_id))
{
}

int Order::get_id() const
{
    return id_;
}

std::string Order::get_symbol() const
{
    return symbol_;
}

double Order::get_price() const
{
    return price_;
}

int Order::get_quantity() const
{
    return quantity_;
}

OrderType Order::get_type() const
{
    return type_;
}

std::string Order::get_client_id() const
{
    return client_id_;
}

void Order::reduce_quantity(int quantity)
{
    quantity_ -= quantity;
}

void Order::set_id(const std::string &id_str)
{
    id_ = std::stoi(id_str);
}

void Order::set_client_id(const std::string &client_id)
{
    client_id_ = client_id;
}