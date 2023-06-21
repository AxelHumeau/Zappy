/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Camera
*/

#include "Camera.hpp"

namespace ZappyGui {
    Camera::Camera(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name): AGameObject(sceneManager) {
        _camera = std::shared_ptr<Ogre::Camera>(sceneManager->createCamera(name), ZappyGui::Nop{});
        _node->attachObject(_camera.get());
    }
}
