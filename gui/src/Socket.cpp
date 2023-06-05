/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Socket
*/

#include "Socket.hpp"

#include <unistd.h>

Network::Socket::Socket(std::string const &ip, uint16_t port):
    _ip(inet_addr(ip.c_str())), _port(port)
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

Network::Socket::Socket(uint32_t ip, uint16_t port):
    _ip(ip), _port(port)
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

void Network::Socket::send()
{
    auto str = getString(false);
    if (str.has_value())
        write(fd, str.value().c_str(), str.value().size());
}

Network::Socket::ConnectionException::ConnectionException(uint16_t port, uint32_t ip):
    _port(port), _ip(ip)
{
    std::string base = "Couldn't connect to ";

    base += std::to_string(_ip >> 3) + ".";
    base += std::to_string((_ip | 0b0100) >> 2) + ".";
    base += std::to_string((_ip | 0b0010) >> 1) + ".";
    base += std::to_string(_ip | 0b0001) + ":";
    base += std::to_string(_port);
}
