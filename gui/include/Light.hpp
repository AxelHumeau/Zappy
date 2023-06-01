/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Light
*/

#ifndef LIGHT_HPP_
    #define LIGHT_HPP_
    #include "GameObject.hpp"

namespace ZappyGui {
    class Light : public AGameObject {
        public:
            Light(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name, Ogre::Light::LightTypes type = Ogre::Light::LT_POINT);
            ~Light() {};

            void setType(Ogre::Light::LightTypes type) { _light->setType(type); }
            void setDiffuseColour(float red, float green, float blue) { _light->setDiffuseColour(red, green, blue); }
            void setSpecularColour(float red, float green, float blue) { _light->setSpecularColour(red, green, blue); }
            void setSpotlightRange(const Ogre::Radian &innerAngle, const Ogre::Radian &outerAngle, Ogre::Real falloff = (1.0F)) { _light->setSpotlightRange(innerAngle, outerAngle, falloff); }
        private:
            std::shared_ptr<Ogre::Light> _light;
    };
}

#endif /* !LIGHT_HPP_ */
