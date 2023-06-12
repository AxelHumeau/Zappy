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
#include "Socket.hpp"
#include <cstdlib>
#include <thread>
#include "SafeQueue.hpp"

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
    ZappyGui::Light light2(renderer.getSceneManager(), "light2", Ogre::Light::LT_SPOTLIGHT);
    light2.setDiffuseColour(1, 1, 1);
    light2.setSpecularColour(1, 1, 1);
    light2.setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    light2.setPosition(0, 0, 15);
    light2.setDirection(0, 0, -1);

    ZappyGui::Light light(renderer.getSceneManager(), "light", Ogre::Light::LT_DIRECTIONAL);
    light.setDiffuseColour(1, 1, 1);
    light.setSpecularColour(1, 1, 1);
    light.setDirection(0, -1, -1);

    // also need to tell where we are

    // create the camera
    ZappyGui::Camera camera(renderer.getSceneManager(), "myCam");
    std::shared_ptr<ZappyGui::Camera> cam = std::make_shared<ZappyGui::Camera>(camera);
    cam->setNearClipDistance(0.05); // specific to this sample
    cam->setAutoAspectRatio(true);
    cam->setPosition(0, 0, 0);
    cam->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // and tell it to render into the main window
    renderer.registerCamera(cam);

    // finally something to render
    ZappyGui::GameObject jerome(renderer.getSceneManager(), "Mathias.mesh");
    jerome.setPosition(0, 0, -5);
    jerome.lookAt(Ogre::Vector3(10, 10, 0), Ogre::Node::TS_PARENT);

    ZappyGui::Tilemap t(renderer.getSceneManager(), 10, 10);
    t.setPosition(0.0f, 0.0f, -10.0f);
    ZappyGui::Vector2i size = t.getSize();
    for (int y = 0; y < size.data[1]; y++) {
        for (int x = 0; x < size.data[0]; x++) {
            ZappyGui::GameObject obj(renderer.getSceneManager(), "hamster.mesh");
            std::shared_ptr<ZappyGui::GameObject> g = std::make_shared<ZappyGui::GameObject>(obj);
            t[y][x].bindGameObject(g);
        }
    }
    t.setTileSize(2.0f, 2.0f);

    float deltaTime = renderer.getDeltaTime();
    std::string rec;

    while (!renderer.isDone())
    {
        renderer.updateDeltaTime();
        deltaTime = renderer.getDeltaTime();

        while (receive.tryPop(rec))
            std::cout << rec << std::endl;

        renderer.event();
        renderer.processInputs();
        jerome.setRotation(Ogre::Radian(1.0f * deltaTime), Ogre::Radian(-1.0f * deltaTime), Ogre::Radian(5.0f * deltaTime));
        renderer.renderOneFrame();
    }
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

void server(int port, std::string ip, bool &isClosed, std::mutex &mutex, SafeQueue<std::string> &receive, SafeQueue<std::string> &requests)
{
    receive.push("Connected");
    while (1)
    {
        mutex.lock();
        if (isClosed)
            break;
        mutex.unlock();
    }

    // int i = 0;

    // try {
    //     Network::Socket socket(ip, port);
    //     while (true) { //TODO: change with window closing condition
    //         if (i % 10 != 0)
    //             socket.addToBuffer("a", false);
    //         else
    //             socket.addToBuffer("\n", false);
    //         socket.select();
    //         socket.send();
    //         i++;
    //     }
    // } catch (Network::Socket::ConnectionException const &e) {
    //     std::cerr << e.what() << std::endl;
    //     return 84;
    // }
}

int gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests)
{
    ZappyGui::Renderer renderer(std::string("Zappy"), 1920, 1080, "./gui/config/resources");
    createScene(renderer, receive, requests);
    return 0;
}

int main(int argc, char *argv[])
{
    int port = 0;
    std::string ip("");
    bool isClosed = false;
    SafeQueue<std::string> receive;
    SafeQueue<std::string> requests;
    std::mutex mutex;

    if (getOptions(argc - 1, argv + 1, port, ip) == -1)
        return 84;

    std::thread serverThread(server, port, ip, std::ref(isClosed), std::ref(mutex), std::ref(receive), std::ref(requests));

    std::thread guiThread(gui, std::ref(receive), std::ref(requests));
    guiThread.join();

    mutex.lock();
    isClosed = true;
    mutex.unlock();
    serverThread.join();
    return 0;
}
