/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

namespace ZappyGui {

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

}

