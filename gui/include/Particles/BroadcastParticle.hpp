/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** BroadcastParticle
*/

#pragma once
#include "Particles/Particle.hpp"
#include <cmath>

#define TO_RAD(t) (t * M_PI / 180)

namespace ZappyGui {
    /// @brief Particle effect for broadcast
    class BroadcastParticle {
    public:
        /// @brief Construct the object
        /// @param sceneManager the scene manager
        /// @param origin the point of origin
        /// @param frequency time unit of the game
        BroadcastParticle(std::shared_ptr<Ogre::SceneManager> sceneManager, Vector3 origin, size_t frequency);
        ~BroadcastParticle() = default;

    private:
        std::shared_ptr<Ogre::SceneManager> _sceneManager;
        std::list<Particle> particles;
        Vector3 _origin;
    };
}
