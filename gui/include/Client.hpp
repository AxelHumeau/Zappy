/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_
    #include <iostream>
    #include <unordered_map>
    #include <functional>
    #include <mutex>
    #include "Socket.hpp"
    #include "SafeQueue.hpp"

namespace Network {
    class Client {
        public:
            /// @brief Create a new client, open a new socket and try to connect to the given ip and port
            /// @param ip to connect
            /// @param port to connect
            /// @return The new client instance or ConnectionException if an error occurs
            Client(std::string ip, uint16_t port);
            ~Client() {};
            /// @brief run the client main loop. the loop will process the incoming response and send the pending requests
            /// @param isClosed condition to end the loop
            /// @param mutex used to ckeck the isClosed condition safely
            /// @param receive a SafeQueue that store the received response
            /// @param requests a SafeQueue that store the pending requests
            void run(bool &isClosed, std::mutex &mutex, SafeQueue<std::string> &receive, SafeQueue<std::string> &requests);

        private:
            Network::Socket _socket;
    };
}

#endif /* !CLIENT_HPP_ */
