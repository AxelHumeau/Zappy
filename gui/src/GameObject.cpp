/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameObject
*/

#include "GameObject.hpp"

namespace ZappyGui {
    GameObject::GameObject(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName) {
        _entity = std::shared_ptr<Ogre::Entity> (sceneManager->createEntity(meshName), ZappyGui::nop{});
        _node = std::shared_ptr<Ogre::SceneNode>(sceneManager->getRootSceneNode()->createChildSceneNode(), ZappyGui::nop{});
        _node->attachObject(_entity.get());
    }

    Camera::Camera(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name) {
        _camera = std::shared_ptr<Ogre::Camera>(sceneManager->createCamera("myCam"), ZappyGui::nop{});
        _node = std::shared_ptr<Ogre::SceneNode>(sceneManager->getRootSceneNode()->createChildSceneNode(), ZappyGui::nop{});
        _node->attachObject(_camera.get());
    }
}
