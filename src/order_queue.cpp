#include "..\include\order_queue.h"

void OrderQueue::add_order(const Order &order)
{
    orders_.push(order);
}

Order OrderQueue::get_next_order()
{
    Order next_order = orders_.front();
    orders_.pop();
    return next_order;
}
