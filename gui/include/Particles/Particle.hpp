/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Particle
*/

#pragma once
#include "GameObject.hpp"

namespace ZappyGui {
    class Particle : public AGameObject{
    public:
        Particle(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &particle);
        ~Particle() {_sceneManager->destroyParticleSystem(particleSystem.get());};

    private:
        std::unique_ptr<Ogre::ParticleSystem, Nop> particleSystem;
    };
}
