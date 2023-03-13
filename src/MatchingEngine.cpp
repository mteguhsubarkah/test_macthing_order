#include "..\include\MatchingEngine.h"
#include "..\include\OrderIdGenerator.h"
#include "..\include\DataGenerator.h"
#include <iostream>

MatchingEngine::MatchingEngine(int port)
    : tcp_server_(std::make_unique<TcpServer>("127.0.0.1", port)),
      order_book_buy_(std::make_unique<OrderBook>(OrderType::Buy)),
      order_book_sell_(std::make_unique<OrderBook>(OrderType::Sell))
{
    // Set the callback function for when a new client connects
    tcp_server_->set_on_connect([this](int socket)
                                { std::cout << "New client connected with socket " << socket << std::endl; });

    // Set the callback function for when a client disconnects
    tcp_server_->set_on_disconnect([this](int socket)
                                   { std::cout << "Client with socket " << socket << " disconnected" << std::endl; });

    // Set the callback function for when a message is received
    tcp_server_->set_on_message([this](int socket, const std::string &message)
                                {
        std::cout << "Received message from client with socket " << socket << ": " << message << std::endl;

        // Parse the message and create a new order
        auto order = DataGenerator::parse_order_message(message);
        // Create an instance of OrderIDGenerator
        OrderIDGenerator order_id_generator;

        // Assign an order ID to the order
        order->set_id(order_id_generator.generate_order_id());


        // Add the order to the appropriate order book
        if (order->get_type() == OrderType::Buy) {
            // order_book_buy_->add_order(order);
            // order_book_buy_->add_order(order.get());
            order_book_buy_->add_order(std::shared_ptr<Order>(std::move(order)));
        } else {
            order_book_sell_->add_order(std::shared_ptr<Order>(std::move(order)));
        }

        // Match orders and generate trades
        auto trades = trade_book_.match_orders(order_book_buy_.get(), order_book_sell_.get());

        // Send trade confirmation messages to the clients involved in the trades
        for (const auto& trade : trades) {
            auto message = DataGenerator::generate_trade_message(trade);
            if (trade.get_buy_socket() != -1) {
                tcp_server_->send(trade.get_buy_socket(), message);
            }
            if (trade.get_sell_socket() != -1) {
                tcp_server_->send(trade.get_sell_socket(), message);
            }
        } });
}

void MatchingEngine::start()
{
    tcp_server_->start();
}
