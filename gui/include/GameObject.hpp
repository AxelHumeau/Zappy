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
    #include "Utils.hpp"

namespace ZappyGui {

    class IGameObject {
        public:
            virtual ~IGameObject() {}

            virtual void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z) = 0;
            virtual void lookAt(
                const Ogre::Vector3 &targetPoint,
                Ogre::Node::TransformSpace relativeTo,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) = 0;
            virtual void setDirection(
                Ogre::Real x,
                Ogre::Real y,
                Ogre::Real z,
                Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) = 0;
        protected:
            std::shared_ptr<Ogre::SceneNode> _node;
    };

    class AGameObject : public IGameObject {
        public:
            ~AGameObject() = default;

            void setPosition(Ogre::Real x, Ogre::Real y, Ogre ::Real z) { _node->setPosition(x, y, z); }
            void lookAt(
                const Ogre::Vector3 &targetPoint,
                Ogre::Node::TransformSpace relativeTo,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) { _node->lookAt(targetPoint, relativeTo, localDirectionVector); }
            void setDirection(
                Ogre::Real x,
                Ogre::Real y,
                Ogre::Real z,
                Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) { _node->setDirection(x, y, z, relativeTo, localDirectionVector); }
            void setRotation(const Ogre::Radian &roll, const Ogre::Radian &pitch, const Ogre::Radian &yaw) {
                _node->roll(roll);
                _node->pitch(pitch);
                _node->yaw(yaw);
            }
    };

    class GameObject : public AGameObject {
        public:
            GameObject(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName);
            ~GameObject() {};
        private:
            std::shared_ptr<Ogre::Entity> _entity;
    };
}

#endif /* !GAMEOBJECT_HPP_ */
