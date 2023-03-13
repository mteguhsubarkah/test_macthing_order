#include "../include/TradeBook.h"
#include <algorithm>

void TradeBook::add_trade(const Trade &trade)
{
    trades_.push_back(trade);
}

const std::vector<Trade> &TradeBook::get_trades() const
{
    return trades_;
}

std::vector<Trade> TradeBook::match_orders(OrderBook *buy_order_book, OrderBook *sell_order_book)
{
    std::vector<Trade> trades;

    while (true)
    {
        // Get the best buy and sell orders
        const auto &best_buy_order = buy_order_book->get_best_order();
        const auto &best_sell_order = sell_order_book->get_best_order();

        // Check if there are no more buy or sell orders
        if (!best_buy_order || !best_sell_order)
        {
            break;
        }

        // Check if the buy order price is less than or equal to the sell order price
        if (best_buy_order->get_price() <= best_sell_order->get_price())
        {
            // Determine the quantity of the trade
            int quantity = std::min(best_buy_order->get_quantity(), best_sell_order->get_quantity());

            // Create a trade and add it to the trade book
            Trade trade(best_buy_order->get_client_id(), best_sell_order->get_client_id(),
                        best_buy_order->get_price(), quantity, buy_order_book->get_socket(), sell_order_book->get_socket());

            add_trade(trade);
            trades.push_back(trade);

            // Update the order quantities
            best_buy_order->reduce_quantity(quantity);
            best_sell_order->reduce_quantity(quantity);

            // Remove the buy and sell orders if their quantities have been fulfilled
            if (best_buy_order->get_quantity() == 0)
            {
                buy_order_book->remove_order(best_buy_order);
            }
            if (best_sell_order->get_quantity() == 0)
            {
                sell_order_book->remove_order(best_sell_order);
            }
        }
        else
        {
            break;
        }
    }

    return trades;
}