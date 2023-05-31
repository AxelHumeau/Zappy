/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP_
    #define GAMEOBJECT_HPP_
    #include <OGRE/Ogre.h>
    #include <string>
    #include <memory>

namespace Zappy {

    class IGameObject {
        public:
            virtual ~IGameObject() {}

            virtual void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z) = 0;
        protected:
            std::shared_ptr<Ogre::SceneNode> _node;
    };

    class AGameObject : public IGameObject {
        public:
            ~AGameObject() = default;

            void setPosition(Ogre::Real x, Ogre::Real y, Ogre ::Real z) { _node->setPosition(x, y, z); }
    };

    class GameObject : public AGameObject {
        public:
            GameObject(std::unique_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName);
            ~GameObject() {};
        private:
            std::shared_ptr<Ogre::Entity> _entity;
    };
}

#endif /* !GAMEOBJECT_HPP_ */