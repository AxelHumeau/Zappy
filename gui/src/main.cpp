/*
** EPITECH PROJECT, 2023
** basicOgreApp
** File description:
** main
*/

#include <OGRE/Bites/OgreWindowEventUtilities.h>
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Tilemap.hpp"
#include <iostream>
#include "Client.hpp"
#include <cstdlib>
#include <thread>
#include "SafeQueue.hpp"
#include "Gui.hpp"
#include <time.h>

static int getOptions(int nb_args, char *args[], int &port, std::string &ip)
{
    if (nb_args <= 0)
        return 0;
    std::string str(*args);
    if (str == "-p") {
        if (++args == NULL)
            return -1;
        port = atoi(*args);
        if (port <= 0 || port >= MAX_PORT_NUMBER)
            return -1;
        return getOptions(nb_args - 2, args + 1, port, ip);
    }
    if (str == "-h") {
        if (++args == NULL)
            return -1;
        ip = *args;
        if (ip == "localhost")
            ip = "127.0.0.1";
        return getOptions(nb_args - 2, args + 1, port, ip);
    }
    std::cerr << "Unknown option: " << str << std::endl;
    return -1;
}

void server(Network::Client &client, bool &isClosed, SafeQueue<std::string> &receive, SafeQueue<std::string> &requests)
{
    client.run(isClosed, receive, requests);
    receive.push("quit\n");
}

void gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests, int &exitCode)
{
    try {
        ZappyGui::Gui gui(receive, requests, 0.05f);
        gui.initialize();
        gui.run();
        exitCode = 0;
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        exitCode = 84;
    }
}

int main(int argc, char *argv[])
{
    int port = 0;
    std::string ip("");
    bool isClosed = false;
    SafeQueue<std::string> receive;
    SafeQueue<std::string> requests;

    srand(time(NULL));
    if (getOptions(argc - 1, argv + 1, port, ip) == -1)
        return 84;
    try {
        int result = 0;
        Network::Client client(ip, port);
        std::thread serverThread(server, std::ref(client), std::ref(isClosed), std::ref(receive), std::ref(requests));
        std::thread guiThread(gui, std::ref(receive), std::ref(requests), std::ref(result));
        guiThread.join();

        isClosed = true;
        serverThread.join();
        return result;
    } catch (Network::Socket::ConnectionException const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
