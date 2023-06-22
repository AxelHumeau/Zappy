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
    class BroadcastParticle {
    public:
        BroadcastParticle(std::shared_ptr<Ogre::SceneManager> sceneManager, Vector3 origin);
        ~BroadcastParticle() = default;

    private:
        std::shared_ptr<Ogre::SceneManager> _sceneManager;
        std::list<Particle> particles;
        Vector3 _origin;
    };
}
