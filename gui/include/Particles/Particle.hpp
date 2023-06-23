/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Particle
*/

#pragma once
#include "GameObject.hpp"

namespace ZappyGui {
    /// @brief Particle object
    class Particle : public AGameObject{
    public:
        /// @brief Construct the particle
        /// @param sceneManager the scene manager
        /// @param particle name of the particule to create
        Particle(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &particle);
        /// @brief Destructor, must be called before destructor of the scene manager
        ~Particle() {_sceneManager->destroyParticleSystem(particleSystem.get());};
        /// @brief get the particle system
        /// @return a reference to the particle system
        Ogre::ParticleSystem &getParticleSystem() {return *particleSystem;}

    private:
        std::unique_ptr<Ogre::ParticleSystem, Nop> particleSystem;
    };
}
