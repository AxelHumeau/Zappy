/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#include <OGRE/OgreRay.h>
#include "Gui.hpp"
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
    _tilePanels.reset(new std::map<std::string, std::unique_ptr<ZappyGui::Tile, Nop>>);
    _renderer->setTilePanels(_tilePanels);
    _playerPanels.reset(new std::map<std::string, std::unique_ptr<ZappyGui::Player, Nop>>);
    _renderer->setPlayerPanels(_playerPanels);
}

void ZappyGui::Gui::initialize()
{

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

    _renderer->setSkyBoxVisibility(false);

    std::string command;
    while (!_renderer->isDone() && _mapWidth == 0 && _mapHeight == 0)
    {
        _renderer->updateDeltaTime();

        if (_receive.tryPop(command))
            processCommand(command);

        _renderer->event();
        _renderer->mouseEvent();
        _renderer->renderOneFrame();
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

    _renderer->setSkyBoxVisibility(true);
    tilemap->setTileSize(2.0f, 2.0f, 2.0f);
    setTilemap(tilemap);
    _sceneQuery.reset(_renderer->getSceneManager()->createRayQuery(Ogre::Ray(), Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK));
    _sceneQuery->setSortByDistance(true);
}

void ZappyGui::Gui::run()
{
    float deltaTime = _renderer->getDeltaTime();
    std::string command;

    while (!_renderer->isDone())
    {
        _renderer->updateDeltaTime();
        deltaTime = _renderer->getDeltaTime();

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
        _checkMouseClick();
        _updatePanels();
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

std::vector<std::size_t> ZappyGui::Gui::convertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex, std::size_t endIndex)
{
    if (endIndex == static_cast<std::size_t>(-1))
        endIndex = args.size() - 1;
    return _ImplconvertArgsToSize_t(args, startIndex, endIndex);
}

std::vector<std::size_t> ZappyGui::Gui::_ImplconvertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex, std::size_t endIndex)
{
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

void ZappyGui::Gui::setDone(bool done)
{
    _renderer->setDone(done);
}

void ZappyGui::Gui::_checkMouseClick()
{
    ZappyGui::Vector2 pos;

    if (_renderer->mouseClicksEmpty())
        return;

    pos = _renderer->popMouseClicks();
    Ogre::Ray ray = _renderer->getCamera()->getCamera()->getCameraToViewportRay(pos.x, pos.y);
    _sceneQuery->setRay(ray);
    Ogre::RaySceneQueryResult res = _sceneQuery->execute();
    if (res.size() == 0)
        return;

    std::string entityName = "";
    std::unique_ptr<Tile, Nop> tile = nullptr;
    std::unique_ptr<Player, Nop> player = nullptr;

    for (Ogre::RaySceneQueryResult::iterator it = res.begin(); it != res.end(); it++)
    {
        entityName = it->movable->getName();
        tile = _getTileByName(entityName);
        if (tile != nullptr)
            break;
        player = _getPlayerByName(entityName);
        if (player != nullptr)
            break;
    }

    if (tile != nullptr)
        _createTilePanel(std::move(tile), pos);
    if (player != nullptr)
        _createPlayerPanel(std::move(player), pos);
}

void ZappyGui::Gui::_updatePanels()
{
    VectorMap<std::string, std::shared_ptr<ZappyGui::Panel>> &panels = _renderer->getPanels();

    for (auto &tile : (*_tilePanels.get()))
    {
        if (panels.find(tile.first) == panels.end())
            _tilePanels->erase(tile.first);
        else
        {
            panels[tile.first]->textSetText(tile.first + "_foodNb", std::to_string(tile.second->getResourceAmount(ZappyGui::ResourceType::Food)));
            panels[tile.first]->textSetText(tile.first + "_linemateNb", std::to_string(tile.second->getResourceAmount(ZappyGui::ResourceType::Linemate)));
            panels[tile.first]->textSetText(tile.first + "_deraumereNb", std::to_string(tile.second->getResourceAmount(ZappyGui::ResourceType::Deraumere)));
            panels[tile.first]->textSetText(tile.first + "_siburNb", std::to_string(tile.second->getResourceAmount(ZappyGui::ResourceType::Sibur)));
            panels[tile.first]->textSetText(tile.first + "_mendianeNb", std::to_string(tile.second->getResourceAmount(ZappyGui::ResourceType::Mendiane)));
            panels[tile.first]->textSetText(tile.first + "_phirasNb", std::to_string(tile.second->getResourceAmount(ZappyGui::ResourceType::Phiras)));
            panels[tile.first]->textSetText(tile.first + "_thystameNb", std::to_string(tile.second->getResourceAmount(ZappyGui::ResourceType::Thystame)));
        }
    }
}

void ZappyGui::Gui::_createDefaultTextArea(std::shared_ptr<ZappyGui::Panel> p, std::string name, ZappyGui::Vector2i pos, std::string text)
{
    p->addTextArea(name, pos.data[0], pos.data[1], "defaultFont");
    p->textSetText(name, text);
    p->textSetCharacterHeight(name, 30);
    p->textSetColorBottom(name, Ogre::ColourValue(0.3, 0.5, 0.3));
    p->textSetColorTop(name, Ogre::ColourValue(0.5, 0.7, 0.5));
}

std::unique_ptr<ZappyGui::Tile, ZappyGui::Nop> ZappyGui::Gui::_getTileByName(std::string name)
{
    std::unique_ptr<ZappyGui::Tile, Nop> tile = nullptr;
    ZappyGui::Vector2i size = _tilemap->getSize();

    for (int y = 0; y < size.data[1]; y++)
    {
        for (int x = 0; x < size.data[0]; x++)
        {
            if ((*_tilemap.get())[y][x].getGameobject().getEntityName() == name)
            {
                tile.reset(&(*_tilemap.get())[y][x]);
                return std::move(tile);
            }
        }
    }
    return std::move(tile);
}

void ZappyGui::Gui::_createTilePanel(std::unique_ptr<Tile, Nop> tile, ZappyGui::Vector2 pos)
{
    static std::size_t idTile;

    idTile++;
    std::string name = "Overlay_Tile_" + std::to_string(idTile);
    std::shared_ptr<ZappyGui::Panel> p(new ZappyGui::Panel(_renderer->getOverlay(), name, true));
    p->panelSetPosition((pos.x * 1920) - 200, (pos.y * 1080) - 10);
    p->panelSetDimensions(400, 200);
    p->panelSetMaterial("RedTransparent");

    p->addTextArea(name + "_title", 200, 15, "defaultFont");
    p->textSetAlignment(name + "_title", Ogre::TextAreaOverlayElement::Center);
    p->textSetText(name + "_title", "Tile " + std::to_string(tile->getPosition().data[0]) + " " + std::to_string(tile->getPosition().data[1]));
    p->textSetCharacterHeight(name + "_title", 50);
    p->textSetColorBottom(name + "_title", Ogre::ColourValue(0.3, 0.5, 0.3));
    p->textSetColorTop(name + "_title", Ogre::ColourValue(0.5, 0.7, 0.5));

    _createDefaultTextArea(p, name + "_food", ZappyGui::Vector2i(20, 70), "Food");
    _createDefaultTextArea(p, name + "_foodNb", ZappyGui::Vector2i(170, 70), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Food)));

    _createDefaultTextArea(p, name + "_linemate", ZappyGui::Vector2i(20, 100), "Linemate");
    _createDefaultTextArea(p, name + "_linemateNb", ZappyGui::Vector2i(170, 100), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Linemate)));

    _createDefaultTextArea(p, name + "_deraumere", ZappyGui::Vector2i(20, 130), "Deraumere");
    _createDefaultTextArea(p, name + "_deraumereNb", ZappyGui::Vector2i(170, 130), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Deraumere)));

    _createDefaultTextArea(p, name + "_sibur", ZappyGui::Vector2i(20, 160), "Sibur");
    _createDefaultTextArea(p, name + "_siburNb", ZappyGui::Vector2i(170, 160), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Sibur)));

    _createDefaultTextArea(p, name + "_mendiane", ZappyGui::Vector2i(220, 70), "Mendiane");
    _createDefaultTextArea(p, name + "_mendianeNb", ZappyGui::Vector2i(360, 70), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Mendiane)));

    _createDefaultTextArea(p, name + "_phiras", ZappyGui::Vector2i(220, 100), "Phiras");
    _createDefaultTextArea(p, name + "_phirasNb", ZappyGui::Vector2i(360, 100), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Phiras)));

    _createDefaultTextArea(p, name + "_thystame", ZappyGui::Vector2i(220, 130), "Thystame");
    _createDefaultTextArea(p, name + "_thystameNb", ZappyGui::Vector2i(360, 130), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Thystame)));

    p->addCloseButton(ZappyGui::Rect{20, 15, 24, 24}, "PanelCloseButton_default", "PanelCloseButton_hover", "PanelCloseButton_click");

    _tilePanels->insert({name, std::move(tile)});
    _renderer->getPanels().push({name, std::move(p)});
}

std::unique_ptr<ZappyGui::Player, ZappyGui::Nop> ZappyGui::Gui::_getPlayerByName(std::string name)
{
    std::unique_ptr<ZappyGui::Player, Nop> player = nullptr;
    std::map<std::string, std::list<ZappyGui::Player>> &teams = _game.getTeams();

    for (auto &t : teams)
    {
        for (auto p = t.second.begin(); p != t.second.end(); p++)
        {
            if (p->getEntityName() == name)
            {
                player.reset(&(*p));
                return std::move(player);
            }
        }
    }
    return std::move(player);
}

void ZappyGui::Gui::_createPlayerPanel(std::unique_ptr<Player, Nop> player, ZappyGui::Vector2 pos)
{
    static std::size_t idPlayer;

    idPlayer++;
    std::string name = "Overlay_Player_" + std::to_string(idPlayer);
    std::shared_ptr<ZappyGui::Panel> p(new ZappyGui::Panel(_renderer->getOverlay(), name, true));
    p->panelSetPosition((pos.x * 1920) - 200, (pos.y * 1080) - 10);
    p->panelSetDimensions(400, 200);
    p->panelSetMaterial("RedTransparent");

    p->addTextArea(name + "_title", 200, 15, "defaultFont");
    p->textSetAlignment(name + "_title", Ogre::TextAreaOverlayElement::Center);
    p->textSetText(name + "_title", "Player " + std::to_string(player->getId()));
    p->textSetCharacterHeight(name + "_title", 50);
    p->textSetColorBottom(name + "_title", Ogre::ColourValue(0.3, 0.5, 0.3));
    p->textSetColorTop(name + "_title", Ogre::ColourValue(0.5, 0.7, 0.5));

    p->addCloseButton(ZappyGui::Rect{20, 15, 24, 24}, "PanelCloseButton_default", "PanelCloseButton_hover", "PanelCloseButton_click");

    _playerPanels->insert({name, std::move(player)});
    _renderer->getPanels().push({name, std::move(p)});
}
