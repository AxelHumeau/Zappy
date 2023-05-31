/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameObject
*/

#include "GameObject.hpp"

namespace Zappy {
    GameObject::GameObject(std::unique_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName) {
        _entity = std::make_shared<Ogre::Entity>(sceneManager->createEntity(meshName));
        _node = std::make_shared<Ogre::SceneNode>(sceneManager->getRootSceneNode()->createChildSceneNode());
        _node->attachObject(_entity.get());
    }
}
