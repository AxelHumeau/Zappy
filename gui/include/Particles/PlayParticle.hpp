/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** PlayParticle
*/

#pragma once
#include "Particles/BroadcastParticle.hpp"

namespace ZappyGui {
    void playBroadcastParticle(std::shared_ptr<Ogre::SceneManager> sceneManager, ZappyGui::Vector3 origin);
}
