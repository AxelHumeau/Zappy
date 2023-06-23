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
    _playerPanels.reset(new std::map<std::string, std::size_t>);
    _renderer->setPlayerPanels(_playerPanels);
}

void ZappyGui::Gui::initialize()
{

    std::shared_ptr<ZappyGui::Camera> cam = std::make_shared<ZappyGui::Camera>(_renderer->getSceneManager(), "myCam");
    cam->setNearClipDistance(0.05);
    cam->setAutoAspectRatio(true);
    cam->setPosition(0, 0, 0);
    cam->lookAt(Ogre::Vector3(0, 0, 1), Ogre::Node::TS_PARENT);
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
    float tileSize = 2.0f;
    std::shared_ptr<ZappyGui::Tilemap> tilemap = std::make_shared<ZappyGui::Tilemap>(_renderer->getSceneManager(), _mapWidth, _mapHeight);
    tilemap->setPosition((_mapWidth * tileSize) / 2, -(tileSize * 2) * 2, _mapWidth * tileSize + (_mapWidth * tileSize) / 4);
    ZappyGui::Vector2i size = tilemap->getSize();
    for (int y = 0; y < size.data[1]; y++) {
        for (int x = 0; x < size.data[0]; x++) {
            std::shared_ptr<ZappyGui::GameObject> obj_ptr = std::make_shared<ZappyGui::GameObject>(_renderer->getSceneManager(), "hamster.mesh");
            (*tilemap)[y][x].bindGameObject(obj_ptr);
        }
    }

    _renderer->setSkyBoxVisibility(true);
    tilemap->setTileSize(tileSize, tileSize, tileSize);
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

        for (auto &broadParticle: _broadcastParticles)
            broadParticle.updateTimer();

        if (_waitedServerUpdateDelay >= _minDelayServerUpdates) {
            _game.update(_requests, deltaTime);
            _tilemap->update(_requests);
            _waitedServerUpdateDelay = 0.0f;
        } else
            _waitedServerUpdateDelay += deltaTime;

        _game.updatePlayers(deltaTime);

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

void ZappyGui::Gui::addBroadcastParticle(Vector3 position)
{
    _broadcastParticles.remove_if([](auto& particlePtr){ return particlePtr == nullptr; });
    _broadcastParticles.emplace_back(std::chrono::milliseconds(100000 / _timeUnit),
        _renderer->getSceneManager(), position, _timeUnit);
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
    for (auto &player : (*_playerPanels.get()))
    {
        if (panels.find(player.first) == panels.end())
            _playerPanels->erase(player.first);
        else
        {
            try
            {
                ZappyGui::Player &p = _game.getPlayer(player.second);

                panels[player.first]->textSetText(player.first + "_levelNb", std::to_string(p.getLevel()));
                std::string pos = std::to_string(p.getMapPosition().data[0]) + " " + std::to_string(p.getMapPosition().data[1]);
                panels[player.first]->textSetText(player.first + "_posNb", pos);

                panels[player.first]->textSetText(player.first + "_foodNb", std::to_string(p.getInventoryAmount(ZappyGui::ResourceType::Food)));
                panels[player.first]->textSetText(player.first + "_linemateNb", std::to_string(p.getInventoryAmount(ZappyGui::ResourceType::Linemate)));
                panels[player.first]->textSetText(player.first + "_deraumereNb", std::to_string(p.getInventoryAmount(ZappyGui::ResourceType::Deraumere)));
                panels[player.first]->textSetText(player.first + "_siburNb", std::to_string(p.getInventoryAmount(ZappyGui::ResourceType::Sibur)));
                panels[player.first]->textSetText(player.first + "_mendianeNb", std::to_string(p.getInventoryAmount(ZappyGui::ResourceType::Mendiane)));
                panels[player.first]->textSetText(player.first + "_phirasNb", std::to_string(p.getInventoryAmount(ZappyGui::ResourceType::Phiras)));
                panels[player.first]->textSetText(player.first + "_thystameNb", std::to_string(p.getInventoryAmount(ZappyGui::ResourceType::Thystame)));
            }
            catch (const ZappyGui::PlayerUndefinedError)
            {
                panels.erase(player.first);
                _playerPanels->erase(player.first);
                continue;
            }
        }
    }
}

void ZappyGui::Gui::_createDefaultTextArea(std::shared_ptr<ZappyGui::Panel> p, std::string name, ZappyGui::Vector2i pos, std::string text)
{
    p->addTextArea(name, pos.data[0], pos.data[1], "defaultFont");
    p->textSetText(name, text);
    p->textSetCharacterHeight(name, 30);
    p->textSetColorBottom(name, Ogre::ColourValue(0.7, 0.7, 0.7));
    p->textSetColorTop(name, Ogre::ColourValue(0.8, 0.8, 0.8));
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
    std::string name;
    std::shared_ptr<ZappyGui::Panel> p;

    idTile++;
    name = "Overlay_Tile_" + std::to_string(idTile);
    p.reset(new ZappyGui::Panel(_renderer->getOverlay(), name, true));
    p->panelSetPosition((pos.x * _renderer->getDimensions().data[0]) - 200, (pos.y * _renderer->getDimensions().data[1]) - 10);
    p->panelSetDimensions(400, 200);
    p->panelSetMaterial("TilePanelMaterial");

    p->addTextArea(name + "_title", 200, 12, "defaultFont");
    p->textSetAlignment(name + "_title", Ogre::TextAreaOverlayElement::Center);
    p->textSetText(name + "_title", "Tile " + std::to_string(tile->getPosition().data[0]) + " " + std::to_string(tile->getPosition().data[1]));
    p->textSetCharacterHeight(name + "_title", 50);
    p->textSetColorBottom(name + "_title", Ogre::ColourValue(0.7, 0.7, 0.7));
    p->textSetColorTop(name + "_title", Ogre::ColourValue(0.8, 0.8, 0.8));

    _createDefaultTextArea(p, name + "_food", ZappyGui::Vector2i(20, 75), "Food");
    _createDefaultTextArea(p, name + "_foodNb", ZappyGui::Vector2i(170, 75), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Food)));

    _createDefaultTextArea(p, name + "_linemate", ZappyGui::Vector2i(20, 105), "Linemate");
    _createDefaultTextArea(p, name + "_linemateNb", ZappyGui::Vector2i(170, 105), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Linemate)));

    _createDefaultTextArea(p, name + "_deraumere", ZappyGui::Vector2i(20, 135), "Deraumere");
    _createDefaultTextArea(p, name + "_deraumereNb", ZappyGui::Vector2i(170, 135), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Deraumere)));

    _createDefaultTextArea(p, name + "_sibur", ZappyGui::Vector2i(20, 165), "Sibur");
    _createDefaultTextArea(p, name + "_siburNb", ZappyGui::Vector2i(170, 165), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Sibur)));

    _createDefaultTextArea(p, name + "_mendiane", ZappyGui::Vector2i(220, 75), "Mendiane");
    _createDefaultTextArea(p, name + "_mendianeNb", ZappyGui::Vector2i(360, 75), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Mendiane)));

    _createDefaultTextArea(p, name + "_phiras", ZappyGui::Vector2i(220, 105), "Phiras");
    _createDefaultTextArea(p, name + "_phirasNb", ZappyGui::Vector2i(360, 105), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Phiras)));

    _createDefaultTextArea(p, name + "_thystame", ZappyGui::Vector2i(220, 135), "Thystame");
    _createDefaultTextArea(p, name + "_thystameNb", ZappyGui::Vector2i(360, 135), std::to_string(tile->getResourceAmount(ZappyGui::ResourceType::Thystame)));

    p->addCloseButton(ZappyGui::Rect{20, 20, 24, 24}, "PanelCloseButton_default", "PanelCloseButton_hover", "PanelCloseButton_click");

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
    std::string name;
    std::string strPos;
    std::shared_ptr<ZappyGui::Panel> p;

    idPlayer++;
    name = "Overlay_Player_" + std::to_string(idPlayer);
    p.reset(new ZappyGui::Panel(_renderer->getOverlay(), name, true));

    p->panelSetPosition((pos.x * _renderer->getDimensions().data[0]) - 200, (pos.y * _renderer->getDimensions().data[1]) - 10);
    p->panelSetDimensions(400, 300);
    p->panelSetMaterial("PlayerPanelMaterial");

    p->addTextArea(name + "_title", 200, 12, "defaultFont");
    p->textSetAlignment(name + "_title", Ogre::TextAreaOverlayElement::Center);
    p->textSetText(name + "_title", "Player " + std::to_string(player->getId()));
    p->textSetCharacterHeight(name + "_title", 50);
    p->textSetColorBottom(name + "_title", Ogre::ColourValue(0.7, 0.7, 0.7));
    p->textSetColorTop(name + "_title", Ogre::ColourValue(0.8, 0.8, 0.8));

    _createDefaultTextArea(p, name + "_team", ZappyGui::Vector2i(100, 75), "Team");
    _createDefaultTextArea(p, name + "_teamName", ZappyGui::Vector2i(225, 75), player->getTeam());

    _createDefaultTextArea(p, name + "_level", ZappyGui::Vector2i(100, 105), "Level");
    _createDefaultTextArea(p, name + "_levelNb", ZappyGui::Vector2i(225, 105), std::to_string(player->getLevel()));

    strPos = std::to_string(player->getMapPosition().data[0]) + " " + std::to_string(player->getMapPosition().data[1]);
    _createDefaultTextArea(p, name + "_pos", ZappyGui::Vector2i(100, 135), "Position");
    _createDefaultTextArea(p, name + "_posNb", ZappyGui::Vector2i(225, 135), strPos);

    _createDefaultTextArea(p, name + "_food", ZappyGui::Vector2i(20, 170), "Food");
    _createDefaultTextArea(p, name + "_foodNb", ZappyGui::Vector2i(170, 170), std::to_string(player->getInventoryAmount(ZappyGui::ResourceType::Food)));

    _createDefaultTextArea(p, name + "_linemate", ZappyGui::Vector2i(20, 200), "Linemate");
    _createDefaultTextArea(p, name + "_linemateNb", ZappyGui::Vector2i(170, 200), std::to_string(player->getInventoryAmount(ZappyGui::ResourceType::Linemate)));

    _createDefaultTextArea(p, name + "_deraumere", ZappyGui::Vector2i(20, 230), "Deraumere");
    _createDefaultTextArea(p, name + "_deraumereNb", ZappyGui::Vector2i(170, 230), std::to_string(player->getInventoryAmount(ZappyGui::ResourceType::Deraumere)));

    _createDefaultTextArea(p, name + "_sibur", ZappyGui::Vector2i(20, 260), "Sibur");
    _createDefaultTextArea(p, name + "_siburNb", ZappyGui::Vector2i(170, 260), std::to_string(player->getInventoryAmount(ZappyGui::ResourceType::Sibur)));

    _createDefaultTextArea(p, name + "_mendiane", ZappyGui::Vector2i(220, 170), "Mendiane");
    _createDefaultTextArea(p, name + "_mendianeNb", ZappyGui::Vector2i(360, 170), std::to_string(player->getInventoryAmount(ZappyGui::ResourceType::Mendiane)));

    _createDefaultTextArea(p, name + "_phiras", ZappyGui::Vector2i(220, 200), "Phiras");
    _createDefaultTextArea(p, name + "_phirasNb", ZappyGui::Vector2i(360, 200), std::to_string(player->getInventoryAmount(ZappyGui::ResourceType::Phiras)));

    _createDefaultTextArea(p, name + "_thystame", ZappyGui::Vector2i(220, 230), "Thystame");
    _createDefaultTextArea(p, name + "_thystameNb", ZappyGui::Vector2i(360, 230), std::to_string(player->getInventoryAmount(ZappyGui::ResourceType::Thystame)));

    p->addCloseButton(ZappyGui::Rect{20, 20, 24, 24}, "PanelCloseButton_default", "PanelCloseButton_hover", "PanelCloseButton_click");

    _playerPanels->insert({name, player->getId()});
    _renderer->getPanels().push({name, std::move(p)});
}
