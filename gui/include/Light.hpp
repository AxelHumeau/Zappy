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
    /// @brief represent a Light
    class Light : public AGameObject {
        public:
            Light(std::shared_ptr<Ogre::SceneManager> sceneManager, const Ogre::String &name, Ogre::Light::LightTypes type = Ogre::Light::LT_POINT);
            ~Light() {};

            /// @brief set the light type (ex: point light, spot light, directional light)
            /// @param type to set (Ogre::Light::LightTypes)
            void setType(Ogre::Light::LightTypes type) { _light->setType(type); }
            /// @brief set the diffuse color of the light by the given rgb value
            /// @param red r color value
            /// @param green g color value
            /// @param blue b color value
            void setDiffuseColour(float red, float green, float blue) { _light->setDiffuseColour(red, green, blue); }
            /// @brief set the specular color of the light by the given rgb value
            /// @param red r color value
            /// @param green g color value
            /// @param blue b color value
            void setSpecularColour(float red, float green, float blue) { _light->setSpecularColour(red, green, blue); }
            /** Sets the range of a spotlight, i.e. the angle of the inner and outer cones
                and the rate of falloff between them.
            @param innerAngle
                Angle covered by the bright inner cone
                @note
                    The inner cone applicable only to Direct3D, it'll always treat as zero in OpenGL.
            @param outerAngle
                Angle covered by the outer cone
            @param falloff
                The rate of falloff between the inner and outer cones. 1.0 means a linear falloff,
                less means slower falloff, higher means faster falloff.
            */
            void setSpotlightRange(const Ogre::Radian &innerAngle, const Ogre::Radian &outerAngle, Ogre::Real falloff = (1.0F)) { _light->setSpotlightRange(innerAngle, outerAngle, falloff); }
        private:
            std::shared_ptr<Ogre::Light> _light;
    };
}

#endif /* !LIGHT_HPP_ */
