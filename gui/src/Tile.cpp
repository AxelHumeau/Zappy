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

    TileUndifinedResourceTypeError::TileUndifinedResourceTypeError(std::string resourceType)
    : message("Undifined resource type \"" + resourceType + "\"") {}
    char const *TileUndifinedResourceTypeError::what() const noexcept { return message.c_str(); }

    Tile::Tile(int x, int y): _x{x}, _y{y} {
        _resources["Food"] = 0;
        _resources["Linemate"] = 0;
        _resources["Deraumere"] = 0;
        _resources["Sibur"] = 0;
        _resources["Mendiane"] = 0;
        _resources["Phiras"] = 0;
        _resources["Thystame"] = 0;
    }

    ZappyGui::GameObject const &Tile::getGameobject() {
        if (_gameobject == nullptr)
            throw TileNoGameobjectBoundError();
        return *_gameobject.get();
    }

    std::size_t Tile::getResourceAmount(const std::string &resourceType) {
        if (_resources.find(resourceType) == _resources.end())
            throw TileUndifinedResourceTypeError(resourceType);
        return _resources[resourceType];
    }
}
