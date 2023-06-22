/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** PlayParticle
*/

#include "Particles/PlayParticle.hpp"

void ZappyGui::playBroadcastParticle(std::shared_ptr<Ogre::SceneManager> sceneManager, ZappyGui::Vector3 origin)
{
    BroadcastParticle particle(sceneManager, origin);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
