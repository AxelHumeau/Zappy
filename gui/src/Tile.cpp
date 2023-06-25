/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"
#include <cstdlib>
#include <time.h>

namespace ZappyGui {

    TileNoGameobjectBoundError::TileNoGameobjectBoundError(): message("No Gameobject bound to tile") {}
    char const *TileNoGameobjectBoundError::what() const noexcept { return message.c_str(); }

    Tile::Tile(std::shared_ptr<Ogre::SceneManager> sceneManager, int x, int y)
    : _sceneManager{sceneManager}, _x{x}, _y{y}{
        _resources[ResourceType::Food] = {0, {}};
        _resources[ResourceType::Linemate] = {0, {}};
        _resources[ResourceType::Deraumere] = {0, {}};
        _resources[ResourceType::Sibur] = {0, {}};
        _resources[ResourceType::Mendiane] = {0, {}};
        _resources[ResourceType::Phiras] = {0, {}};
        _resources[ResourceType::Thystame] = {0, {}};
    }

    ZappyGui::GameObject &Tile::getGameobject() {
        if (_gameobject == nullptr)
            throw TileNoGameobjectBoundError();
        return *_gameobject.get();
    }

    std::size_t Tile::getResourceAmount(const ZappyGui::ResourceType &resourceType) {
        if (_resources.find(resourceType) == _resources.end())
            throw UndefinedResourceTypeError();
        return _resources[resourceType].first;
    }

    void Tile::setResourceAmount(const ZappyGui::ResourceType &resourceType, std::size_t amount) {
        if (_resources.find(resourceType) == _resources.end())
            throw UndefinedResourceTypeError();
        _resources[resourceType].first = amount;

        _updateResourceOnTile();
    }

    void Tile::_placeResourceOnTile(std::list<ZappyGui::GameObject> &resourceList, std::string mesh, int precision, float availableSpace) {
        ZappyGui::Vector3 position;
        Vector2 positionOffset;
        Vector2i flooredTileSize;
        int rotation;

        position = ZappyGui::Vector3(
            _tilemapOrigin.x - _tileSize.x * _x,
            _tilemapOrigin.y + _tileSize.y / 2,
            _tilemapOrigin.z - _tileSize.z * _y
        );
        flooredTileSize.data[0] = static_cast<int>(_tileSize.x);
        flooredTileSize.data[1] = static_cast<int>(_tileSize.z);
        positionOffset.x = rand() % (flooredTileSize.data[0] * precision) - flooredTileSize.data[0] * precision / 2;
        positionOffset.y = rand() % (flooredTileSize.data[1] * precision) - flooredTileSize.data[1] * precision / 2;
        positionOffset.x *= availableSpace;
        positionOffset.y *= availableSpace;
        rotation = rand() % 360;
        resourceList.emplace_back(_sceneManager, mesh);
        resourceList.back().setPosition(position.x + positionOffset.x / precision, position.y, position.z + positionOffset.y / precision);
        resourceList.back().setOrientation(Ogre::Quaternion(Ogre::Degree(rotation), Vector3(0, 1, 0)));
    }

    void Tile::_updateResourceOnTile() {
        for (auto &[resourceType, resource] : _resources) {
            if (resource.first == 0 && resource.second.size() != 0) {
                resource.second.clear();
                continue;
            }
            if (resource.first >= 1 && resource.second.size() == 0)
                _placeResourceOnTile(resource.second, ResourceMeshes.at(resourceType));
        }
    }
}
