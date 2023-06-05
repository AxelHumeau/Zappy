/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Socket
*/

#pragma once
#include <string>
#include <optional>
#include <exception>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GET_NTH_BYTE(number, n) (number >> (8 * n)) & 0xff

namespace Network {
    class Socket {
    public:
        Socket(std::string const &ip, uint16_t port);
        Socket(uint32_t ip, uint16_t port);
        Socket(Socket const &) = delete;
        ~Socket();
        void select();
        bool isReadSet() const { return FD_ISSET(fd, &readfds); }
        bool isWriteSet() const { return FD_ISSET(fd, &writefds); }
        std::optional<std::string> getString(bool isRead = true);
        void addToBuffer(std::string const &str, bool isRead = true);
        void send();

        class ConnectionException : public std::exception {
        public:
            ConnectionException(uint16_t port, uint32_t ip);
            const char *what() const noexcept override { return base.c_str(); }

        private:
            uint16_t _port;
            uint32_t _ip;
            std::string base;
        };

    private:
        uint16_t _port;
        uint32_t _ip;
        int fd;
        fd_set readfds;
        fd_set writefds;
        std::string r_buffer;
        std::string s_buffer;
    };
}
