/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>

void ZappyGui::GuiCommands::quit(std::vector<std::string>) {}
void ZappyGui::GuiCommands::msz(std::vector<std::string>) {}

ZappyGui::Gui::Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests): _receive{receive}, _requests{requests} {
    _renderer = std::make_unique<ZappyGui::Renderer>(std::string("Zappy"), 1920, 1080, "./gui/config/resources");
}

void ZappyGui::Gui::initialize() {
    ZappyGui::Camera camera(_renderer->getSceneManager(), "myCam");
    std::shared_ptr<ZappyGui::Camera> cam = std::make_shared<ZappyGui::Camera>(camera);
    cam->setNearClipDistance(0.05); // specific to this sample
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

        while (_receive.tryPop(command))
            std::cout << command << std::endl;
        // processCommand(command);

        _renderer->event();
        _renderer->renderSdl2();
    }
    ZappyGui::Tilemap tilemap(_renderer->getSceneManager(), 10, 10);
    tilemap.setPosition(0.0f, 0.0f, -10.0f);
    ZappyGui::Vector2i size = tilemap.getSize();
    for (int y = 0; y < size.data[1]; y++) {
        for (int x = 0; x < size.data[0]; x++) {
            ZappyGui::GameObject obj(_renderer->getSceneManager(), "hamster.mesh");
            std::shared_ptr<ZappyGui::GameObject> g = std::make_shared<ZappyGui::GameObject>(obj);
            tilemap[y][x].bindGameObject(g);
        }
    }
    tilemap.setTileSize(2.0f, 2.0f);
}

void ZappyGui::Gui::run() {
    float deltaTime = _renderer->getDeltaTime();
    std::string command;

    while (!_renderer->isDone())
    {
        _renderer->updateDeltaTime();
        deltaTime = _renderer->getDeltaTime();

        // while (receive.tryPop(command))
        //     processCommand(command);

        _renderer->event();
        _renderer->processInputs();
        _renderer->renderOneFrame();
    }
}
