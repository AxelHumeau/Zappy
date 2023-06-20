/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

namespace ZappyGui {

    Player::Player(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName, std::size_t id): GameObject(sceneManager, meshName), _id{id} {
        setFacing(3);
        _inventory[ResourceType::Food] = 0;
        _inventory[ResourceType::Linemate] = 0;
        _inventory[ResourceType::Deraumere] = 0;
        _inventory[ResourceType::Sibur] = 0;
        _inventory[ResourceType::Mendiane] = 0;
        _inventory[ResourceType::Phiras] = 0;
        _inventory[ResourceType::Thystame] = 0;
    }

    void Player::setMapPosition(std::shared_ptr<ZappyGui::Tilemap> tilemap, size_t x, size_t y) {
        _mapPosition.data[0] = x; _mapPosition.data[1] = y;
        ZappyGui::Tile &tile = (*tilemap)[_mapPosition.data[1]][_mapPosition.data[0]];
        tilemap->placeGameObjectOnTile(tile, *this);
    }

    void Player::setFacing(size_t orientation) {
        switch (orientation) {
        case 1:
            _orientation = Orientation::North;
            setOrientation(Ogre::Quaternion(Ogre::Degree(180),Vector3(0, 1, 0)));
            break;
        case 2:
            setOrientation(Ogre::Quaternion(Ogre::Degree(90),Vector3(0, 1, 0)));
            _orientation = Orientation::East;
            break;
        case 3:
            setOrientation(Ogre::Quaternion(Ogre::Degree(0),Vector3(0, 1, 0)));
            _orientation = Orientation::South;
            break;
        case 4:
            setOrientation(Ogre::Quaternion(Ogre::Degree(-90),Vector3(0, 1, 0)));
            _orientation = Orientation::West;
            break;
        }
    }

    std::size_t Player::getInventoryAmount(const ResourceType &resourceType) {
        if (_inventory.find(resourceType) == _inventory.end())
            throw UndifinedResourceTypeError();
        return _inventory[resourceType];
    }
    void Player::setInventoryAmount(const ResourceType &resourceType, std::size_t amount) {
        if (_inventory.find(resourceType) == _inventory.end())
            throw UndifinedResourceTypeError();
        _inventory[resourceType] = amount;
    }
}

