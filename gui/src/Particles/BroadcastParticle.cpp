/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** BroadcastParticle
*/

#include "Particles/BroadcastParticle.hpp"

ZappyGui::BroadcastParticle::BroadcastParticle(std::shared_ptr<Ogre::SceneManager> sceneManager, Vector3 origin):
    _sceneManager(sceneManager), _origin(origin)
{
    for (double t = 0; t < 360; t += 1) {
        particles.emplace_back(_sceneManager, "OneDirection");
        particles.back().setPosition(_origin.x, _origin.y, _origin.z);
        particles.back().getParticleSystem().getEmitter(0)->setDirection({_origin.x + 3 * cosf(TO_RAD(t)), 0, _origin.z + 3 * sinf(TO_RAD(t))});
    }
}
