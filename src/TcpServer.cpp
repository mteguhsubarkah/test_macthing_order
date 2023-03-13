#include "..\include\TcpServer.h"
#include "..\include\tcp_connection.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

TcpServer::TcpServer(const std::string &address, int port) : address_(address), port_(port)
{
#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        throw std::runtime_error("WSAStartup failed");
    }
#endif

    // Create socket
    listen_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socket_ == -1)
    {
        throw std::runtime_error("Could not create socket");
    }

    // Bind socket to port
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_);

    if (bind(listen_socket_, (sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        throw std::runtime_error("Could not bind socket to port");
    }

    // Listen for incoming connections
    int backlog = SOMAXCONN;
    int result = listen(listen_socket_, backlog);
    if (result == -1)
    {
        throw std::runtime_error("Could not listen on socket");
    }
}

TcpServer::~TcpServer()
{
#ifdef _WIN32
    closesocket(listen_socket_);
    WSACleanup();
#else
    close(listen_socket_);
#endif
}

int TcpServer::accept_connection()
{
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    int client_socket = ::accept(m_socket, (struct sockaddr *)&client_address, &client_address_len);

    if (client_socket == -1)
    {
        throw std::runtime_error("Failed to accept client connection");
    }

    return client_socket;
}
