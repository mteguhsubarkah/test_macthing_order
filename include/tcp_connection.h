#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <string>

class TcpConnection
{
public:
    TcpConnection(int socket, const std::string &client_address);
    ~TcpConnection();

    void send(const char *data, int length);
    int receive(char *buffer, int buffer_size);

private:
    int socket_;
    std::string client_address_;
    int listen_socket_;
};

#endif // TCP_CONNECTION_H
