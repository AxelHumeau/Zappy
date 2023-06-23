/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"

namespace ZappyGui {

    TileNoGameobjectBoundError::TileNoGameobjectBoundError(): message("No Gameobject bound to tile") {}
    char const *TileNoGameobjectBoundError::what() const noexcept { return message.c_str(); }

    Tile::Tile(int x, int y): _x{x}, _y{y} {
        _resources[ResourceType::Food] = 0;
        _resources[ResourceType::Linemate] = 0;
        _resources[ResourceType::Deraumere] = 0;
        _resources[ResourceType::Sibur] = 0;
        _resources[ResourceType::Mendiane] = 0;
        _resources[ResourceType::Phiras] = 0;
        _resources[ResourceType::Thystame] = 0;
    }

    ZappyGui::GameObject &Tile::getGameobject() {
        if (_gameobject == nullptr)
            throw TileNoGameobjectBoundError();
        return *_gameobject.get();
    }

    std::size_t Tile::getResourceAmount(const ZappyGui::ResourceType &resourceType) {
        if (_resources.find(resourceType) == _resources.end())
            throw UndefinedResourceTypeError();
        return _resources[resourceType];
    }

    void Tile::setResourceAmount(const ZappyGui::ResourceType &resourceType, std::size_t amount) {
        if (_resources.find(resourceType) == _resources.end())
            throw UndefinedResourceTypeError();
        _resources[resourceType] = amount;
    }
}
