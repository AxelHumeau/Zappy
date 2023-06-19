/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tilemap
*/

#include "Tilemap.hpp"
#include <iostream>

namespace ZappyGui {
    Tilemap::Tilemap(std::shared_ptr<Ogre::SceneManager> sceneManager, int width, int height): _width{width}, _height{height}, AGameObject(sceneManager)
    {
        for (int y = 0; y < _height; y++) {
            _tilemap.emplace_back(std::vector<Tile>());
            for (int x = 0; x < _width; x++)
                _tilemap[y].emplace_back(Tile(x, y));
        }
    }

    void Tilemap::setTileSize(ZappyGui::Real width, ZappyGui::Real height, ZappyGui::Real depth) {
        ZappyGui::Vector3 origin = _node->getPosition();
        ZappyGui::Vector3 position;
        _tileSize.x = width;
        _tileSize.y = height;
        _tileSize.z = depth;

        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                position = ZappyGui::Vector3(origin.x + _tileSize.x * x, origin.y, origin.z - _tileSize.z * y);
                try {
                    _tilemap[y][x].getGameobject().setPosition(position.x, position.y, position.z);
                } catch (const ZappyGui::TileNoGameobjectBoundError& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }

    void Tilemap::placeGameObjectOnTile(ZappyGui::Tile &tile, ZappyGui::GameObject &obj) {
        ZappyGui::Vector3 finalPosition;
        finalPosition.x = getPosition().x + tile.getPosition().data[0] * _tileSize.x;
        finalPosition.y = getPosition().y + _tileSize.y;
        finalPosition.z = getPosition().z - tile.getPosition().data[1] * _tileSize.z;
        obj.setPosition(finalPosition.x, finalPosition.y, finalPosition.z);
    }

    std::vector<Tile> &Tilemap::operator[](std::size_t index) {
        if (index >= _tilemap.size())
            throw IndexOutOfBoundsError();
        return _tilemap[index];
    }
}
