/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#include "Gui.hpp"
#include <sstream>
#include <iostream>
#include "Panel.hpp"

void ZappyGui::quit(ZappyGui::Gui &gui, std::vector<std::string> args)
{
    gui.setDone(true);
}
void ZappyGui::msz(ZappyGui::Gui &gui, std::vector<std::string> args) {}

ZappyGui::Gui::Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests): _receive{receive}, _requests{requests} {
    _commands.emplace("quit", quit);
    _commands.emplace("msz", msz);
    _renderer = std::make_unique<ZappyGui::Renderer>(std::string("Zappy"), 1920, 1080, "./gui/config/resources");
}

void ZappyGui::Gui::initialize()
{
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

    _renderer->setSkyBoxVisibility(false);
    // _renderer->createTestOverlay();

    std::shared_ptr<ZappyGui::Panel> ol(new ZappyGui::Panel(_renderer->getOverlay(), "testPanel", true));
    ol->panelSetPosition(0, 0);
    ol->panelSetDimensions(300, 110);
    ol->panelSetMaterial("RedTransparent");
    ol->addTextArea("test", 150, 10, "defaultFont");
    ol->textSetAlignment("test", Ogre::TextAreaOverlayElement::Center);
    ol->textSetText("test", "Hello, World!\nYO");
    ol->textSetCharacterHeight("test", 50);
    ol->textSetColorBottom("test", Ogre::ColourValue(0.3, 0.5, 0.3));
    ol->textSetColorTop("test", Ogre::ColourValue(0.5, 0.7, 0.5));
    ol->addCloseButton(ZappyGui::Rect{10, 10, 24, 24}, "PanelCloseButton_default", "PanelCloseButton_hover", "PanelCloseButton_click");

    _renderer->getPanels().push({"testPanel", std::move(ol)});
    std::cout << "SIIIIIIIIIIIIZZZZZZZZZEEEEEEEE " << _renderer->getPanels().size() << std::endl;

    std::shared_ptr<ZappyGui::Panel> ol2(new ZappyGui::Panel(_renderer->getOverlay(), "testPanel2", true));
    ol2->panelSetPosition(0, 0);
    ol2->panelSetDimensions(300, 110);
    ol2->panelSetMaterial("RedTransparent");
    ol2->addTextArea("test2", 150, 10, "defaultFont");
    ol2->textSetAlignment("test2", Ogre::TextAreaOverlayElement::Center);
    ol2->textSetText("test2", "Hello, World!\nHI");
    ol2->textSetCharacterHeight("test2", 50);
    ol2->textSetColorBottom("test2", Ogre::ColourValue(0.3, 0.5, 0.3));
    ol2->textSetColorTop("test2", Ogre::ColourValue(0.5, 0.7, 0.5));
    ol2->addCloseButton(ZappyGui::Rect{10, 10, 24, 24}, "PanelCloseButton_default", "PanelCloseButton_hover", "PanelCloseButton_click");

    _renderer->getPanels().push({"testPanel2", std::move(ol2)});
    std::cout << "SIIIIIIIIIIIIZZZZZZZZZEEEEEEEE " << _renderer->getPanels().size() << std::endl;

    std::string command;
    while (!_renderer->isDone() && _mapWidth == 0 && _mapHeight == 0)
    {
        _renderer->updateDeltaTime();

        while (_receive.tryPop(command))
            processCommand(command);

        _renderer->event();
        _renderer->dragPanel();
        _renderer->renderOneFrame();
    }
    if (_renderer->isDone())
        return;
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

    _renderer->setSkyBoxVisibility(true);
}

void ZappyGui::Gui::run()
{
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
    }
}

void ZappyGui::Gui::processCommand(std::string command)
{
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

void ZappyGui::Gui::setDone(bool done)
{
    _renderer->setDone(done);
}
