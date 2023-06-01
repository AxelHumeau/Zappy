/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Camera
*/

#include "Camera.hpp"

namespace ZappyGui {
    Camera::Camera(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name) {
        _camera = std::shared_ptr<Ogre::Camera>(sceneManager->createCamera(name), ZappyGui::nop{});
        _node = std::shared_ptr<Ogre::SceneNode>(sceneManager->getRootSceneNode()->createChildSceneNode(), ZappyGui::nop{});
        _node->attachObject(_camera.get());
    }
}
