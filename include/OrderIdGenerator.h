#ifndef ORDER_ID_GENERATOR_H
#define ORDER_ID_GENERATOR_H

#include <string>

class OrderIDGenerator
{
public:
    OrderIDGenerator();

    std::string generate_order_id();

private:
    int latest_order_id_;
};

#endif /* ORDER_ID_GENERATOR_H */
