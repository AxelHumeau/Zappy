/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

namespace ZappyGui {

    Player::Player(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName, std::size_t id): GameObject(sceneManager, meshName), _id{id} {
        _inventory[ResourceType::Food] = 0;
        _inventory[ResourceType::Linemate] = 0;
        _inventory[ResourceType::Deraumere] = 0;
        _inventory[ResourceType::Sibur] = 0;
        _inventory[ResourceType::Mendiane] = 0;
        _inventory[ResourceType::Phiras] = 0;
        _inventory[ResourceType::Thystame] = 0;
    }

    Real facingToAngle(const size_t orientation) {
        switch (orientation) {
        case 1:
            return 0;
        case 2:
            return 90;
        case 3:
            return 180;
        case 4:
            return 270;
        }
        return 0;
    }

    void Player::setMapPosition(std::shared_ptr<ZappyGui::Tilemap> tilemap, size_t x, size_t y) {
        _mapPosition.data[0] = x;
        _mapPosition.data[1] = y;
        ZappyGui::Tile &tile = (*tilemap)[_mapPosition.data[1]][_mapPosition.data[0]];
    }

    void Player::setFacingAndPosition(size_t orientation) {
        switch (orientation) {
        case 1:
            _facing = Orientation::North;
            setOrientation(Ogre::Quaternion(Ogre::Degree(0),Vector3(0, 1, 0)));
            break;
        case 2:
            _facing = Orientation::East;
            setOrientation(Ogre::Quaternion(Ogre::Degree(270),Vector3(0, 1, 0)));
            break;
        case 3:
            _facing = Orientation::South;
            setOrientation(Ogre::Quaternion(Ogre::Degree(180),Vector3(0, 1, 0)));
            break;
        case 4:
            _facing = Orientation::West;
            setOrientation(Ogre::Quaternion(Ogre::Degree(90),Vector3(0, 1, 0)));
            break;
        }
    }

    void Player::setFacing(size_t orientation) {
        switch (orientation) {
        case 1:
            _facing = Orientation::North;
            break;
        case 2:
            _facing = Orientation::East;
            break;
        case 3:
            _facing = Orientation::South;
            break;
        case 4:
            _facing = Orientation::West;
            break;
        }
    }

    std::size_t Player::getInventoryAmount(const ResourceType &resourceType) {
        if (_inventory.find(resourceType) == _inventory.end())
            throw UndefinedResourceTypeError();
        return _inventory[resourceType];
    }
    void Player::setInventoryAmount(const ResourceType &resourceType, std::size_t amount) {
        if (_inventory.find(resourceType) == _inventory.end())
            throw UndefinedResourceTypeError();
        _inventory[resourceType] = amount;
    }
}

