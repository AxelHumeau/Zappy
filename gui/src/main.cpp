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

void createScene(ZappyGui::Renderer &renderer, SafeQueue<std::string> &receive, SafeQueue<std::string> &requests)
{
    // Directional light
    // Ogre::Light* directionalLight = scnMgr->createLight("DirectionalLight");
    // directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    // directionalLight->setDiffuseColour(Ogre::ColourValue(1, 0, 0));
    // directionalLight->setSpecularColour(Ogre::ColourValue(1, 0, 0));
    // Ogre::SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    // directionalLightNode->attachObject(directionalLight);
    // directionalLightNode->setPosition(0, 0, 15);
    // directionalLightNode->setDirection(Ogre::Vector3(0, 0, -1));

    // without light we would just get a black screen
    // ZappyGui::Light light2(renderer.getSceneManager(), "light2", Ogre::Light::LT_SPOTLIGHT);
    // light2.setDiffuseColour(1, 1, 1);
    // light2.setSpecularColour(1, 1, 1);
    // light2.setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    // light2.setPosition(0, 0, 15);
    // light2.setDirection(0, 0, -1);

    // also need to tell where we are

    // // create the camera
    // ZappyGui::Camera camera(renderer.getSceneManager(), "myCam");
    // std::shared_ptr<ZappyGui::Camera> cam = std::make_shared<ZappyGui::Camera>(camera);
    // cam->setNearClipDistance(0.05); // specific to this sample
    // cam->setAutoAspectRatio(true);
    // cam->setPosition(0, 0, 0);
    // cam->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // // and tell it to render into the main window
    // renderer.registerCamera(cam);

    // finally something to render
    ZappyGui::GameObject jerome(renderer.getSceneManager(), "Mathias.mesh");
    jerome.setPosition(0, 0, -5);
    jerome.lookAt(Ogre::Vector3(10, 10, 0), Ogre::Node::TS_PARENT);

    // ZappyGui::Tilemap t(renderer.getSceneManager(), 10, 10);
    // t.setPosition(0.0f, 0.0f, -10.0f);
    // ZappyGui::Vector2i size = t.getSize();
    // for (int y = 0; y < size.data[1]; y++) {
    //     for (int x = 0; x < size.data[0]; x++) {
    //         ZappyGui::GameObject obj(renderer.getSceneManager(), "hamster.mesh");
    //         std::shared_ptr<ZappyGui::GameObject> g = std::make_shared<ZappyGui::GameObject>(obj);
    //         t[y][x].bindGameObject(g);
    //     }
    // }
    // t.setTileSize(2.0f, 2.0f);
}

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

int gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests)
{
    ZappyGui::Gui gui(receive, requests, 0.05f);
    gui.initialize();
    gui.run();
    return 0;
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
        Network::Client client(ip, port);
        std::thread serverThread(server, std::ref(client), std::ref(isClosed), std::ref(receive), std::ref(requests));
        std::thread guiThread(gui, std::ref(receive), std::ref(requests));
        guiThread.join();

        isClosed = true;
        serverThread.join();
        return 0;
    } catch (Network::Socket::ConnectionException const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
