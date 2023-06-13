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

    void Client::run(bool &isClosed, SafeQueue<std::string> &receive, SafeQueue<std::string> &requests) {
        std::string request;

        while (!isClosed) {
            _socket.select();
            _socket.receive();
            while (requests.tryPop(request))
                _socket.addToBuffer(request, false);
            _socket.send();
            std::optional<std::string> msg = _socket.getString();
            while (msg.has_value()) {
                receive.push(msg.value());
                msg = _socket.getString();
            }
        }
    }
}
