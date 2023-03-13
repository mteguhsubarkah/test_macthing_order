#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <functional>
#include <string>

class TcpServer
{
public:
    TcpServer(const std::string &address, int port);

    // start listening for incoming connections
    void start();

    // set the callback function for when a new client connects
    void set_on_connect(std::function<void(int)> on_connect);

    // set the callback function for when a client disconnects
    void set_on_disconnect(std::function<void(int)> on_disconnect);

    // set the callback function for when a message is received
    void set_on_message(std::function<void(int, const std::string &)> on_message);

    // send a message to the client with the specified socket
    void send(int socket, const std::string &message);

    // close the connection with the client with the specified socket
    void close(int socket);

    // stop the server
    void stop();

    int accept_connection();

private:
    std::string address_;
    int port_;
    int listen_socket_;
    int m_socket;

    std::function<void(int)> on_connect_;
    std::function<void(int)> on_disconnect_;
    std::function<void(int, const std::string &)> on_message_;
    bool running_;
};

#endif // TCP_SERVER_H
