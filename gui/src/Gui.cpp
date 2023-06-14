/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#include "Gui.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

void ZappyGui::quit(ZappyGui::Gui &gui, std::vector<std::string> args) {
    gui.setDone(true);
}

void ZappyGui::msz(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::pair<size_t, size_t> mapSize = gui.getMapSize();

    if (args.size() != 2 || mapSize.first != 0 || mapSize.second != 0)
        return;
    if (args[0].find('-') != std::string::npos || args[1].find('-') != std::string::npos)
        return;
    gui.setMapSize(strtoul(args[0].c_str(), NULL, 10), strtoul(args[1].c_str(), NULL, 10));
}

void ZappyGui::bct(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;
    std::size_t value;
    if (args.size() != 9)
        return;
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i].find('-') != std::string::npos)
            return;
        value = strtoul(args[i].c_str(), NULL, 10);
        if (value == 0 && args[i] != "0")
            return;
        values.push_back(value);
    }

    std::shared_ptr<ZappyGui::Tilemap> tilemap = gui.getTilemap();
    std::size_t x = values[0];
    std::size_t y = values[1];
    try {
        tilemap->operator[](y)[x].setResourceAmount("Food", values[2]);
        tilemap->operator[](y)[x].setResourceAmount("Linemate", values[3]);
        tilemap->operator[](y)[x].setResourceAmount("Deraumere", values[4]);
        tilemap->operator[](y)[x].setResourceAmount("Sibur", values[5]);
        tilemap->operator[](y)[x].setResourceAmount("Mendiane", values[6]);
        tilemap->operator[](y)[x].setResourceAmount("Phiras", values[7]);
        tilemap->operator[](y)[x].setResourceAmount("Thystame", values[8]);
    } catch (ZappyGui::IndexOutOfBoundsError const &e) {
        return;
    }
}

ZappyGui::Gui::Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests): _receive{receive}, _requests{requests} {
    _commands.emplace("quit", quit);
    _commands.emplace("msz", msz);
    _commands.emplace("bct", bct);
    _renderer = std::make_unique<ZappyGui::Renderer>(std::string("Zappy"), 1920, 1080, "./gui/config/resources");
}

void ZappyGui::Gui::initialize() {
    ZappyGui::Camera camera(_renderer->getSceneManager(), "myCam");
    std::shared_ptr<ZappyGui::Camera> cam = std::make_shared<ZappyGui::Camera>(camera);
    cam->setNearClipDistance(0.05);
    cam->setAutoAspectRatio(true);
    cam->setPosition(0, 0, 0);
    cam->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    _renderer->registerCamera(cam);

    ZappyGui::Light light(_renderer->getSceneManager(), "light", Ogre::Light::LT_DIRECTIONAL);
    light.setDiffuseColour(1, 1, 1);
    light.setSpecularColour(1, 1, 1);
    light.setDirection(0, -1, -1);

    std::string command;
    while (!_renderer->isDone() && _mapWidth == 0 && _mapHeight == 0)
    {
        _renderer->updateDeltaTime();

        if (_receive.tryPop(command))
            processCommand(command);

        _renderer->event();
        _renderer->renderSdl2();
    }
    if (_renderer->isDone())
        return;
    ZappyGui::Tilemap tilemap(_renderer->getSceneManager(), _mapWidth, _mapHeight);
    tilemap.setPosition(0.0f, 0.0f, -10.0f);
    ZappyGui::Vector2i size = tilemap.getSize();
    for (int y = 0; y < size.data[1]; y++) {
        for (int x = 0; x < size.data[0]; x++) {
            ZappyGui::GameObject obj(_renderer->getSceneManager(), "hamster.mesh");
            std::shared_ptr<ZappyGui::GameObject> obj_ptr = std::make_shared<ZappyGui::GameObject>(obj);
            tilemap[y][x].bindGameObject(obj_ptr);
        }
    }
    tilemap.setTileSize(2.0f, 2.0f);
    setTilemap(std::make_shared<ZappyGui::Tilemap>(tilemap));
}

void ZappyGui::Gui::run() {
    float deltaTime = _renderer->getDeltaTime();
    std::string command;

    while (!_renderer->isDone())
    {
        _renderer->updateDeltaTime();
        deltaTime = _renderer->getDeltaTime();

        while (_receive.tryPop(command))
            processCommand(command);

        _renderer->event();
        _renderer->processInputs();
        _renderer->renderOneFrame();
        break;
    }
}

void ZappyGui::Gui::processCommand(std::string command) {
    std::string commandName;
    std::string arg;
    std::vector<std::string> args;
    if (command[command.length() - 1] == '\n')
        command.erase(command.length() - 1);
    std::istringstream ss(command);
    getline(ss, commandName, ' ');
    if (commandName == "")
        return;
    while(getline(ss, arg, ' '))
        args.push_back(arg);
    if (_commands.find(commandName) != _commands.end())
        _commands.at(commandName)(*this, args);
}

void ZappyGui::Gui::setDone(bool done) {
    _renderer->setDone(done);
}