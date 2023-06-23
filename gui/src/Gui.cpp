/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#include "Gui.hpp"
#include "Particles/BroadcastParticle.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

ZappyGui::Gui::Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests, float minDelayServerUpdates):
_receive{receive}, _requests{requests}, _minDelayServerUpdates{minDelayServerUpdates} {
    _waitedServerUpdateDelay = 0.0f;
    _commands.emplace("quit", quit);
    _commands.emplace("msz", msz);
    _commands.emplace("bct", bct);
    _commands.emplace("tna", tna);
    _commands.emplace("pnw", pnw);
    _commands.emplace("pdi", pdi);
    _commands.emplace("ppo", ppo);
    _commands.emplace("plv", plv);
    _commands.emplace("pin", pin);
    _commands.emplace("pex", pex);
    _commands.emplace("pbc", pbc);
    _commands.emplace("pic", pic);
    _commands.emplace("pie", pie);
    _commands.emplace("pfk", pfk);
    _commands.emplace("pdr", pdr);
    _commands.emplace("pgt", pgt);
    _commands.emplace("enw", enw);
    _commands.emplace("ebo", ebo);
    _commands.emplace("edi", edi);
    _commands.emplace("sgt", sgt);
    _commands.emplace("sst", sst);
    _commands.emplace("seg", seg);
    _commands.emplace("smg", smg);
    _commands.emplace("suc", suc);
    _commands.emplace("sbp", sbp);
    _renderer = std::make_unique<ZappyGui::Renderer>(std::string("Zappy"), 1920, 1080, "./gui/config/resources");
}

ZappyGui::Gui::~Gui()
{
    // for (auto& thread: particlesThreads)
    //     thread.join();
}

void ZappyGui::Gui::initialize() {
    std::shared_ptr<ZappyGui::Camera> cam = std::make_shared<ZappyGui::Camera>(_renderer->getSceneManager(), "myCam");
    cam->setNearClipDistance(0.05);
    cam->setAutoAspectRatio(true);
    cam->setPosition(0, 0, 0);
    cam->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    _renderer->registerCamera(cam);

    _lights.emplace_back(_renderer->getSceneManager(), "light", Ogre::Light::LT_DIRECTIONAL);
    _lights.back().setDiffuseColour(1, 1, 1);
    _lights.back().setSpecularColour(1, 1, 1);
    _lights.back().setDirection(0, -1, -1);

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
    std::shared_ptr<ZappyGui::Tilemap> tilemap = std::make_shared<ZappyGui::Tilemap>(_renderer->getSceneManager(), _mapWidth, _mapHeight);
    tilemap->setPosition(0.0f, 0.0f, -10.0f);
    ZappyGui::Vector2i size = tilemap->getSize();
    for (int y = 0; y < size.data[1]; y++) {
        for (int x = 0; x < size.data[0]; x++) {
            std::shared_ptr<ZappyGui::GameObject> obj_ptr = std::make_shared<ZappyGui::GameObject>(_renderer->getSceneManager(), "hamster.mesh");
            (*tilemap)[y][x].bindGameObject(obj_ptr);
        }
    }
    tilemap->setTileSize(2.0f, 2.0f, 2.0f);
    setTilemap(tilemap);
}

void ZappyGui::Gui::run() {
    float deltaTime = _renderer->getDeltaTime();
    std::string command;
    TimerPtr<BroadcastParticle> particlePtr(std::chrono::milliseconds(1000), _renderer->getSceneManager(), Vector3({0, 5, 0}));

    while (!_renderer->isDone())
    {
        _renderer->updateDeltaTime();
        deltaTime = _renderer->getDeltaTime();

        particlePtr.updateTimer();

        if (_waitedServerUpdateDelay >= _minDelayServerUpdates) {
            _game.update(_requests);
            _tilemap->update(_requests);
            _waitedServerUpdateDelay = 0.0f;
        } else
            _waitedServerUpdateDelay += deltaTime;

        while (_receive.tryPop(command))
            processCommand(command);

        _renderer->event();
        _renderer->processInputs();
        _renderer->renderOneFrame();
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

std::vector<std::size_t> ZappyGui::Gui::convertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex, std::size_t endIndex) {
    if (endIndex == static_cast<std::size_t>(-1))
        endIndex = args.size() - 1;
    return _ImplconvertArgsToSize_t(args, startIndex, endIndex);
}

std::vector<std::size_t> ZappyGui::Gui::_ImplconvertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex, std::size_t endIndex) {
    std::vector<std::size_t> values;
    std::size_t value;

    if (startIndex >= args.size() || endIndex >= args.size() || endIndex < startIndex)
        return values;
    for (size_t i = startIndex; i < endIndex + 1; i++) {
        if (args[i].find('-') != std::string::npos) {
            values.clear();
            return values;
        }
        value = strtoul(args[i].c_str(), NULL, 10);
        if (value == 0 && args[i] != "0") {
            values.clear();
            return values;
        }
        values.push_back(value);
    }
    return values;
}

void ZappyGui::Gui::setDone(bool done) {
    _renderer->setDone(done);
}
