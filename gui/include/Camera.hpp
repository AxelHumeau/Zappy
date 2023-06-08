/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_
    #include "GameObject.hpp"

namespace ZappyGui {
    class Camera : public AGameObject {
        public:
            Camera(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name);
            ~Camera() {};

            std::shared_ptr<Ogre::Camera> getCamera() const { return _camera; }
            void setNearClipDistance(Ogre::Real nearDist) { _camera->setNearClipDistance(nearDist); }
            void setAutoAspectRatio(bool autoratio) { _camera->setAspectRatio(autoratio); }
            ZappyGui::Vector3 getDirection() { return _camera->getRealDirection(); }
        private:
            std::shared_ptr<Ogre::Camera> _camera;
    };
}

#endif /* !CAMERA_HPP_ */
