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
#include <cstddef>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GET_NTH_BYTE(number, n) (number >> (8 * n)) & 0xff
#define MAX_PORT_NUMBER 65535

namespace Network {
    /// @brief Class for Socket
    class Socket {
    public:
        /// @brief Constructor of the socket
        /// @param ip string representing ip address to connect to
        /// @param port port to connect to
        /// @param bufferSize size of the temporary buffer when receiving data
        Socket(std::string const &ip, uint16_t port, std::size_t bufferSize = 256);
        /// @brief Constructor of the socket
        /// @param ip number representing ip address to connect to
        /// @param port port to connect to
        /// @param bufferSize size of the buffers
        Socket(uint32_t ip, uint16_t port, std::size_t bufferSize = 256);
        Socket(Socket const &) = delete;
        /// @brief Destructor of the socket, close the socket file descriptor
        ~Socket();
        /// @brief Do a select the read and write fd of the socket
        void select();
        /// @brief Get a string from the buffer
        /// @param isRead true to get string from read buffer, false to get it from write buffer. true by default
        /// @return nullopt if no string is available, otherwise a string
        std::optional<std::string> getString(bool isRead = true);
        /// @brief Add string to the buffer
        /// @param str String to add to the buffer
        /// @param isRead true to put string in the read buffer, false to put it in write buffer. true by default
        void addToBuffer(std::string const &str, bool isRead = true);
        /// @brief Send write buffer content to the socket
        /// @return 0 if successful, 1 if the socket wasn't ready for writing, -1 in case of error
        int send();
        /// @brief Read informations received through the socket and put it in the read buffer
        /// @return 0 if successful, 1 if the socket wasn't ready for reading, -1 in case of error
        int receive();

        /// @brief Exception to handle a connection error
        class ConnectionException : public std::exception {
        public:
            /// @brief Constructor of the exception
            /// @param port the port that the program was tying to connect to
            /// @param ip the ip that the program was tying to connect to
            ConnectionException(uint16_t port, uint32_t ip);
            const char *what() const noexcept override { return base.c_str(); }

        private:
            uint16_t _port;
            uint32_t _ip;
            std::string base;
        };

    private:
        /// @brief Check if the socket is ready to be read, must be called after select
        /// @return true if the socket is ready to be read, false otherwise
        bool isReadSet() const { return FD_ISSET(fd, &readfds); }
        /// @brief Check if the socket is ready to be write, must be called after select
        /// @return true if the socket is ready to be write, false otherwise
        bool isWriteSet() const { return FD_ISSET(fd, &writefds); }

        uint16_t _port;
        uint32_t _ip;
        int fd;
        fd_set readfds;
        fd_set writefds;
        std::string r_buffer;
        std::string s_buffer;
        std::size_t _bufferSize;
    };
}
