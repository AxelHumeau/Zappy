/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** BroadcastParticle
*/

#include "Particles/BroadcastParticle.hpp"

ZappyGui::BroadcastParticle::BroadcastParticle(std::shared_ptr<Ogre::SceneManager> sceneManager, Vector3 origin, size_t frequency):
    _sceneManager(sceneManager), _origin(origin)
{
    std::cout << frequency << std::endl;
    for (double t = 0; t < 360; t += 1) {
        particles.emplace_back(_sceneManager, "OneDirection");
        particles.back().setPosition(_origin.x, _origin.y, _origin.z);
        particles.back().getParticleSystem().getEmitter(0)->setDirection({3 * cosf(TO_RAD(t)), 0, 3 * sinf(TO_RAD(t))});
        particles.back().getParticleSystem().getEmitter(0)->setParticleVelocity(0.3f * frequency);
        particles.back().getParticleSystem().getEmitter(0)->setTimeToLive(500.0f / frequency);
    }
}
