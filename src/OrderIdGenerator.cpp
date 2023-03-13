#include "..\include\OrderIdGenerator.h"

OrderIDGenerator::OrderIDGenerator()
    : latest_order_id_(0)
{
}

std::string OrderIDGenerator::generate_order_id()
{
    latest_order_id_++;
    return std::to_string(latest_order_id_);
}
