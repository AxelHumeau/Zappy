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
    /// @brief Represent a Camera, encapsulating Ogre::Camera
    class Camera : public AGameObject {
        public:
            Camera(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name);
            ~Camera() {};

            /// @brief Return a shared pointer to the camera
            /// @param orderStr the serialization of the order
            /// @return a shared pointer to the stored camera (Ogre::Camera)
            std::shared_ptr<Ogre::Camera> getCamera() const { return _camera; }
            /** Sets the position of the near clipping plane.

                The position of the near clipping plane is the distance from the frustums position to the screen
                on which the world is projected. The near plane distance, combined with the field-of-view and the
                aspect ratio, determines the size of the viewport through which the world is viewed (in world
                coordinates). Note that this world viewport is different to a screen viewport, which has it's
                dimensions expressed in pixels. The frustums viewport should have the same aspect ratio as the
                screen viewport it renders into to avoid distortion.
            @param nearDist
                The distance to the near clipping plane from the frustum in world coordinates.
            */
            void setNearClipDistance(Ogre::Real nearDist) { _camera->setNearClipDistance(nearDist); }
            /** Sets the aspect ratio for the frustum viewport.

                The ratio between the x and y dimensions of the rectangular area visible through the frustum
                is known as aspect ratio: aspect = width / height .
            @par
                The default for most fullscreen windows is 1.3333 - this is also assumed by Ogre unless you
                use this method to state otherwise.
            */
            void setAutoAspectRatio(bool autoratio) { _camera->setAspectRatio(autoratio); }
            /** Gets the real world direction vector of the camera, including any
                rotation inherited from a node attachment. */
            ZappyGui::Vector3 getDirection() { return _camera->getRealDirection(); }
        private:
            std::shared_ptr<Ogre::Camera> _camera;
    };
}

#endif /* !CAMERA_HPP_ */
