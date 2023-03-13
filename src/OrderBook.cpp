#include "../include/OrderBook.h"

void OrderBook::add_order(const std::shared_ptr<Order> &order)
{
    orders_.insert(std::make_pair(order->get_price(), order));
}

void OrderBook::remove_order(const std::shared_ptr<Order> &order)
{
    auto range = orders_.equal_range(order->get_price());
    for (auto it = range.first; it != range.second; ++it)
    {
        if (it->second == order)
        {
            orders_.erase(it);
            break;
        }
    }
}

bool OrderBook::empty() const
{
    return orders_.empty();
}

std::shared_ptr<Order> OrderBook::get_best_order() const
{
    return orders_.begin()->second;
}
