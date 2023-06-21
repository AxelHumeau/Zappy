/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Utils
*/

#include "Utils.hpp"

float CubicEase(ZappyGui::Real Time) {
    float timeSquared = Time * Time;
    return timeSquared / (2.0f * (timeSquared - Time) + 1.0f);
}

ZappyGui::Vector3 ZappyGui::lerp(ZappyGui::Vector3 &start, ZappyGui::Vector3 &end, ZappyGui::Real Time) {
    Time = CubicEase(Time);
    return start + (end - start) * Time;
}

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
