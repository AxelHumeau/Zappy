/*
** EPITECH PROJECT, 2023
** Utils.hpp
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_
    #include "Ogre.h"
    #include <unordered_map>

namespace ZappyGui {

    typedef Ogre::Real Real;
    typedef Ogre::Vector3 Vector3;
    typedef Ogre::Vector2 Vector2;
    typedef Ogre::Vector2i Vector2i;

    Vector3 lerp(Vector3 &start, Vector3 &end, Real Time);
    Real lerpReal(Real &start, Real &end, Real Time);

    enum ResourceType {
        Food,
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame
    };

    static const std::unordered_map<ResourceType, std::string> ResourceMeshes {
        { ResourceType::Food, "Pods.mesh" },
        { ResourceType::Linemate, "GreenCrystal.mesh" },
        { ResourceType::Deraumere, "BlueCrystal.mesh" },
        { ResourceType::Sibur, "PurpleCrystal.mesh" },
        { ResourceType::Mendiane, "YellowCrystal.mesh" },
        { ResourceType::Phiras, "OrangeCrystal.mesh" },
        { ResourceType::Thystame, "RedCrystal.mesh" },
    };

    std::ostream &operator<< (std::ostream &os, ZappyGui::ResourceType type);

    struct Nop
    {
        template <typename T>
        void operator() (T const &) const noexcept { }
    };
}

#endif /* !UTILS_HPP_ */
