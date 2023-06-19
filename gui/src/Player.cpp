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

    void Player::setOrientation(size_t orientation) {
        switch (orientation) {
        case 1:
            _orientation = Orientation::North;
            break;
        case 2:
            _orientation = Orientation::East;
            break;
        case 3:
            _orientation = Orientation::South;
            break;
        case 4:
            _orientation = Orientation::West;
            break;
        default:
            _orientation = Orientation::North;
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

