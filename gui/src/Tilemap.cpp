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
        _node = std::shared_ptr<Ogre::SceneNode>(sceneManager->getRootSceneNode()->createChildSceneNode(), ZappyGui::nop{});
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
                position = ZappyGui::Vector3(origin.x + _tileWidth * x, origin.y, origin.z + _tileHeight * y);
                std::cout << _tilemap[y][x].getPosition().first << std::endl;
                std::shared_ptr<ZappyGui::GameObject> popo = _tilemap[y][x].getGameobject();
                if (popo != nullptr)
                    popo->lookAt(ZappyGui::Vector3(position.x, position.y, position.z), Ogre::Node::TS_PARENT);
            }
        }
    }

    std::vector<Tile> &Tilemap::operator[](std::size_t index) {
        if (index >= _tilemap.size())
            throw IndexOutOfBoundsError();
        return _tilemap[index];
    }
}
