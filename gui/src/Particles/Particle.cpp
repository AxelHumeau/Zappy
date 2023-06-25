/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Particle
*/

#include "Particles/Particle.hpp"

ZappyGui::Particle::Particle(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &particle):
    AGameObject(sceneManager)
{
    static int count = 0;

    particleSystem.reset(_sceneManager->createParticleSystem(particle + "_" + std::to_string(count), particle));
    _node->attachObject(particleSystem.get());
    count++;
}
