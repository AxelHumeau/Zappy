/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tilemap
*/

#include "Tilemap.hpp"
#include <iostream>

namespace ZappyGui {
    Tilemap::Tilemap(std::shared_ptr<Ogre::SceneManager> sceneManager, int width, int height): _width{width}, _height{height} {
        _node = std::shared_ptr<Ogre::SceneNode>(sceneManager->getRootSceneNode()->createChildSceneNode(), ZappyGui::Nop{});
        for (int y = 0; y < _height; y++) {
            _tilemap.push_back(std::vector<Tile>());
            for (int x = 0; x < _width; x++)
                _tilemap[y].push_back(Tile(x, y));
        }
    }

    void Tilemap::setTileSize(ZappyGui::Real width, ZappyGui::Real height) {
        ZappyGui::Vector3 origin = _node->getPosition();
        ZappyGui::Vector3 position;
        _tileWidth = width;
        _tileHeight = height;

        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                position = ZappyGui::Vector3(origin.x + _tileWidth * x, origin.y, origin.z - _tileHeight * y);
                try {
                    ZappyGui::GameObject obj = _tilemap[y][x].getGameobject();
                    obj.setPosition(position.x, position.y, position.z);
                } catch (const ZappyGui::TileNoGameobjectBoundError& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }

    std::vector<Tile> &Tilemap::operator[](std::size_t index) {
        if (index >= _tilemap.size())
            throw IndexOutOfBoundsError();
        return _tilemap[index];
    }
}
