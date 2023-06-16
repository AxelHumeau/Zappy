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
    #include <iostream>

namespace ZappyGui {
    /// @brief Interface representing a generic object in the world
    class IGameObject {
        public:
            virtual ~IGameObject() = default;
            /// @brief Set the position of the object in the world space by the given coordinates
            /// @param x x coordinate
            /// @param y y coordinate
            /// @param z z coordinate
            virtual void setPosition(ZappyGui::Real x, ZappyGui::Real y, ZappyGui::Real z) = 0;
            /// @brief return the position of the object in the world space
            /// @return a ZappyGui::Vector3 containing the object position
            virtual const ZappyGui::Vector3 &getPosition() = 0;
            /// @brief rotate the object toward a targetPoint
            /// @param targetPoint A vector specifying the look at targetPoint.
            /// @param relativeTo The space in which the targetPoint resides
            /// @param localDirectionVector The vector which normally describes the natural direction of the node, usually -Z
            virtual void lookAt(
                const ZappyGui::Vector3 &targetPoint,
                Ogre::Node::TransformSpace relativeTo,
                const ZappyGui::Vector3 &localDirectionVector = Ogre::VectorBase<3, ZappyGui::Real>::NEGATIVE_UNIT_Z
            ) = 0;
            /// @brief set the object's diection to the given direction vector
            /// @param x x coordinate of the direction vector
            /// @param y y coordinate of the direction vector
            /// @param z z coordinate of the direction vector
            /// @param relativeTo The space in which this direction vector is expressed
            /// @param localDirectionVector The vector which normally describes the natural direction of the node, usually -Z
            virtual void setDirection(
                ZappyGui::Real x,
                ZappyGui::Real y,
                ZappyGui::Real z,
                Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT,
                const ZappyGui::Vector3 &localDirectionVector = Ogre::VectorBase<3, ZappyGui::Real>::NEGATIVE_UNIT_Z
            ) = 0;
            /// @brief set the object's rotation from the given roll, pitch, and yaw
            /// @param roll angle in radiant
            /// @param pitch angle in radiant
            /// @param yaw angle in radiant
            virtual void setRotation(const Ogre::Radian &roll, const Ogre::Radian &pitch, const Ogre::Radian &yaw) = 0;
            /// @brief set the object's rotation from the given roll, pitch, and yaw. yaw is used on the world axis
            /// @param roll angle in radiant
            /// @param pitch angle in radiant
            /// @param yaw angle in radiant
            virtual void setRotationWorldYaw(const Ogre::Radian &roll, const Ogre::Radian &pitch, const Ogre::Radian &yaw) = 0;
            /// @brief set the object's orientation
            /// @param q a Quaternion representing the rotation to by applied
            virtual void setOrientation(const Ogre::Quaternion &q) = 0;
            /// @brief return the current orientation of the object
            /// @return the Quaternion representing the object's orientation
            virtual const Ogre::Quaternion &getOrientation() const = 0;
            /// @brief rotate the object around the given axis by the given angle
            /// @param axis Vector3 representing the axis
            /// @param angle to rotate expressed in radians
            virtual void rotate(const ZappyGui::Vector3 &axis, const Ogre::Radian &angle) = 0;
            /// @brief Moves the node along the Cartesian axes
            /// @param d Vector representing the translation.
            /// @param relativeTo The space which this transform is relative to.
            virtual void translate(const ZappyGui::Vector3 &d, Ogre::Node::TransformSpace relativeTo=Ogre::Node::TS_PARENT) = 0;
    };

    /// @brief Abstract class representing a generic object in the world
    class AGameObject : public IGameObject {
        public:
            AGameObject(std::shared_ptr<Ogre::SceneManager> sceneManager);
            ~AGameObject() {
                _node->detachAllObjects();
                _sceneManager->destroySceneNode(_node->getName());
            }
            /// @brief Set the position of the object in the world space by the given coordinates
            /// @param x x coordinate
            /// @param y y coordinate
            /// @param z z coordinate
            void setPosition(ZappyGui::Real x, ZappyGui::Real y, ZappyGui::Real z) override { _node->setPosition(x, y, z); }
            /// @brief return the position of the object in the world space
            /// @return a ZappyGui::Vector3 containing the object position
            const ZappyGui::Vector3 &getPosition() override { return _node->getPosition(); }
            /// @brief rotate the object toward a targetPoint
            /// @param targetPoint A vector specifying the look at targetPoint.
            /// @param relativeTo The space in which the targetPoint resides
            /// @param localDirectionVector The vector which normally describes the natural direction of the node, usually -Z
            void lookAt(
                const ZappyGui::Vector3 &targetPoint,
                Ogre::Node::TransformSpace relativeTo,
                const ZappyGui::Vector3 &localDirectionVector = Ogre::VectorBase<3, ZappyGui::Real>::NEGATIVE_UNIT_Z
            ) override { _node->lookAt(targetPoint, relativeTo, localDirectionVector); }
            /// @brief set the object's diection to the given direction vector
            /// @param x x coordinate of the direction vector
            /// @param y y coordinate of the direction vector
            /// @param z z coordinate of the direction vector
            /// @param relativeTo The space in which this direction vector is expressed
            /// @param localDirectionVector The vector which normally describes the natural direction of the node, usually -Z
            void setDirection(
                ZappyGui::Real x,
                ZappyGui::Real y,
                ZappyGui::Real z,
                Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT,
                const ZappyGui::Vector3 &localDirectionVector = Ogre::VectorBase<3, ZappyGui::Real>::NEGATIVE_UNIT_Z
            ) override { _node->setDirection(x, y, z, relativeTo, localDirectionVector); }
            /// @brief set the object's rotation from the given roll, pitch, and yaw
            /// @param roll angle in radiant
            /// @param pitch angle in radiant
            /// @param yaw angle in radiant
            void setRotation(const Ogre::Radian &roll, const Ogre::Radian &pitch, const Ogre::Radian &yaw) override {
                _node->roll(roll);
                _node->pitch(pitch);
                _node->yaw(yaw);
            }
            /// @brief set the object's rotation from the given roll, pitch, and yaw. yaw is used on the world axis
            /// @param roll angle in radiant
            /// @param pitch angle in radiant
            /// @param yaw angle in radiant
            void setRotationWorldYaw(const Ogre::Radian &roll, const Ogre::Radian &pitch, const Ogre::Radian &yaw) override {
                _node->roll(roll);
                _node->pitch(pitch);
                _node->yaw(yaw, Ogre::Node::TS_WORLD);
            }
            /// @brief set the object's orientation
            /// @param q a Quaternion representing the rotation to by applied
            void setOrientation(const Ogre::Quaternion &q) { _node->setOrientation(q); }
            /// @brief return the current orientation of the object
            /// @return the Quaternion representing the object's orientation
            const Ogre::Quaternion &getOrientation() const { return _node->getOrientation(); }
            /// @brief rotate the object around the given axis by the given angle
            /// @param axis Vector3 representing the axis
            /// @param angle to rotate expressed in radians
            void rotate(const ZappyGui::Vector3 &axis, const Ogre::Radian &angle) { _node->rotate(axis, angle); };
            /// @brief Moves the node along the Cartesian axes
            /// @param d Vector representing the translation.
            /// @param relativeTo The space which this transform is relative to.
            void translate(const ZappyGui::Vector3 &d, Ogre::Node::TransformSpace relativeTo=Ogre::Node::TS_PARENT) override { _node->translate(d, relativeTo); };
        protected:
            std::shared_ptr<Ogre::SceneNode> _node;
            std::shared_ptr<Ogre::SceneManager> _sceneManager;
    };

    /// @brief represent a object in the world that have a model
    class GameObject : public AGameObject {
        public:
            GameObject(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName);
            ~GameObject() { _sceneManager->destroyEntity(_entity->getName()); }
        private:
            std::shared_ptr<Ogre::Entity> _entity;
    };
}

#endif
