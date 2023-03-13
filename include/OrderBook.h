#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <memory>
#include "order.h"

class OrderBook
{
public:
    OrderBook(int socket);
    void add_order(const std::shared_ptr<Order> &order);
    void remove_order(const std::shared_ptr<Order> &order);
    bool empty() const;
    std::shared_ptr<Order> get_best_order() const;
    int get_socket() const;

private:
    std::multimap<double, std::shared_ptr<Order>> orders_;
    int socket_;
};

#endif // ORDER_BOOK_H
