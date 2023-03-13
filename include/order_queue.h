#ifndef ORDER_QUEUE_H
#define ORDER_QUEUE_H

#include "order.h"
#include <queue>

class OrderQueue
{
public:
    OrderQueue() {}
    void add_order(const Order &order);
    Order get_next_order();

private:
    std::queue<Order> orders_;
};

#endif // ORDER_QUEUE_H
