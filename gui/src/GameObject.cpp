/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameObject
*/

#include "GameObject.hpp"

namespace ZappyGui {

    AGameObject::AGameObject(std::shared_ptr<Ogre::SceneManager> sceneManager) {
        static int id;
        _sceneManager = sceneManager;
        _node = std::shared_ptr<Ogre::SceneNode>(_sceneManager->getRootSceneNode()->createChildSceneNode("node_" + std::to_string(id)), ZappyGui::Nop{});
        id++;
    }

    GameObject::GameObject(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName): AGameObject(sceneManager) {
        _entity = std::shared_ptr<Ogre::Entity> (_sceneManager->createEntity(meshName), ZappyGui::Nop{});
        _node->attachObject(_entity.get());
    }
}
