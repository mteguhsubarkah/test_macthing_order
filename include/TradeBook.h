#ifndef TRADE_BOOK_H
#define TRADE_BOOK_H

#include <vector>
#include "Trade.h"
#include "OrderBook.h"

class TradeBook
{
public:
    void add_trade(const Trade &trade);
    const std::vector<Trade> &get_trades() const;
    std::vector<Trade> match_orders(OrderBook *buy_order_book, OrderBook *sell_order_book);

private:
    std::vector<Trade> trades_;
};

#endif // TRADE_BOOK_H
