/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Light
*/

#include "Light.hpp"

namespace ZappyGui {
    Light::Light(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name, Ogre::Light::LightTypes type) {
        _light = std::shared_ptr<Ogre::Light>(sceneManager->createLight(name), ZappyGui::Nop{});
        _light->setType(type);
        _node = std::shared_ptr<Ogre::SceneNode>(sceneManager->getRootSceneNode()->createChildSceneNode(), ZappyGui::Nop{});
        _node->attachObject(_light.get());
    }
}
