/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Utils
*/

#include "Utils.hpp"

std::ostream &ZappyGui::operator<< (std::ostream &os, ZappyGui::ResourceType type) {
    switch (type) {
        case ZappyGui::ResourceType::Food : return os << "Food";
        case ZappyGui::ResourceType::Linemate : return os << "Linemate";
        case ZappyGui::ResourceType::Deraumere : return os << "Deraumere";
        case ZappyGui::ResourceType::Sibur : return os << "Sibur";
        case ZappyGui::ResourceType::Mendiane : return os << "Mendiane";
        case ZappyGui::ResourceType::Phiras : return os << "Phiras";
        case ZappyGui::ResourceType::Thystame : return os << "Thystame";
    }
    return os;
}
