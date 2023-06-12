/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Client
*/

#include "Client.hpp"

namespace Network {
    Client::Client(std::string ip, uint16_t port): _socket{ip, port} {
        _socket.addToBuffer("GRAPHIC\n", false);
        _socket.select();
        _socket.send();
    }

    void Client::run() {
        while (true) {
            _socket.select();
            _socket.receive();
            _socket.send();
            std::optional<std::string> msg = _socket.getString();
            while (msg.has_value()) {
                // _processCommand(msg.value());
                msg = _socket.getString();
            }
        }
    }
}
