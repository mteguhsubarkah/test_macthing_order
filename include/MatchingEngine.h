#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <memory>
#include "OrderBook.h"
#include "TradeBook.h"
#include "tcp_server.h"

class MatchingEngine
{
public:
    MatchingEngine(int port);

    void start();

private:
    std::unique_ptr<TcpServer> tcp_server_;
    std::unique_ptr<OrderBook> order_book_buy_;
    std::unique_ptr<OrderBook> order_book_sell_;
    TradeBook trade_book_;
};

#endif // MATCHING_ENGINE_H
