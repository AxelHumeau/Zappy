/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Socket
*/

#include "Socket.hpp"

#include <unistd.h>
#include <iostream>

Network::Socket::Socket(std::string const &ip, uint16_t port, std::size_t bufferSize):
    _ip(inet_addr(ip.c_str())), _port(port), _bufferSize(bufferSize)
{
    int size_addr = sizeof(struct sockaddr_in);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = _ip;
    if (connect(fd, (struct sockaddr *)&address, size_addr) == -1)
        throw ConnectionException(_port, _ip);
}

Network::Socket::Socket(uint32_t ip, uint16_t port, std::size_t bufferSize):
    _ip(ip), _port(port), _bufferSize(bufferSize)
{
    int size_addr = sizeof(struct sockaddr_in);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = _ip;
    if (connect(fd, (struct sockaddr *)&address, size_addr) == -1)
        throw ConnectionException(_port, _ip);
}

Network::Socket::~Socket()
{
    close(fd);
}

void Network::Socket::select()
{
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(fd, &readfds);
    FD_SET(fd, &writefds);
    ::select(fd + 1, &readfds, &writefds, NULL, NULL);
}

std::optional<std::string> Network::Socket::getString(bool isRead)
{
    std::string &base = isRead ? r_buffer : s_buffer;
    auto pos = base.find('\n');

    std::string result = base.substr(0, pos + 1);
    if (result == base)
        return std::nullopt;
    base = base.substr(pos + 1);
    return result;
}

void Network::Socket::addToBuffer(std::string const &str, bool isRead)
{
    std::string &base = isRead ? r_buffer : s_buffer;

    base += str;
}

int Network::Socket::send()
{
    if (!isWriteSet())
        return 1;
    if (write(fd, s_buffer.c_str(), s_buffer.size()) == -1)
        return -1;
    s_buffer = "";
    return 0;
}

int Network::Socket::receive()
{
    char buffer[_bufferSize];
    int read_char = 0;

    if (!isReadSet())
        return 1;
    do {
        read_char = read(fd, buffer, _bufferSize);
        if (read_char == -1)
            return -1;
        addToBuffer(buffer, read_char);
    } while (read_char > 0);
    return 0;
}

Network::Socket::ConnectionException::ConnectionException(uint16_t port, uint32_t ip):
    _port(port), _ip(ip)
{
    base = "Couldn't connect to ";

    base += std::to_string(GET_NTH_BYTE(_ip, 0)) + ".";
    base += std::to_string(GET_NTH_BYTE(_ip, 1)) + ".";
    base += std::to_string(GET_NTH_BYTE(_ip, 2)) + ".";
    base += std::to_string(GET_NTH_BYTE(_ip, 3)) + ":";
    base += std::to_string(_port);
}
