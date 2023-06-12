/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_
    #include "Socket.hpp"
    #include <iostream>
    #include <unordered_map>
    #include <functional>

namespace Network {

    // static const std::unordered_map<std::string, std::function<void>> commands = {
    //     {"read", }
    // }

    class Client {
        public:
            Client(std::string ip, uint16_t port);
            ~Client() {};
            void run();

        private:
            Network::Socket _socket;
    };
}

#endif /* !CLIENT_HPP_ */
