/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Particle
*/

#include "Particles/Particle.hpp"

ZappyGui::Particle::Particle(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &particle):
    AGameObject(sceneManager), particleSystem(_sceneManager->createParticleSystem(particle, particle))
{
    _node->attachObject(particleSystem.get());
}
