/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tilemap
*/

#ifndef TILEMAP_HPP_
    #define TILEMAP_HPP_
    #include "Tile.hpp"
    #include "GameObject.hpp"
    #include "Error.hpp"
    #include <vector>

namespace ZappyGui {
    class Tilemap : public AGameObject {
        public:
            Tilemap(std::shared_ptr<Ogre::SceneManager> sceneManager, int width, int height);
            ~Tilemap() {};
            void setTileSize(ZappyGui::Real width, ZappyGui::Real height);
            Vector2i getSize() { return Vector2i(_width, _height); }
            Vector2 getTileSize() { return Vector2(_tileWidth, _tileHeight); }

            void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z) { _node->setPosition(x, y, z); }
            void lookAt(
                const Ogre::Vector3 &targetPoint,
                Ogre::Node::TransformSpace relativeTo,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) { throw NotImplementedError(); }
            void setDirection(
                Ogre::Real x,
                Ogre::Real y,
                Ogre::Real z,
                Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) { throw NotImplementedError(); }
            void setRotation(const Ogre::Radian &roll, const Ogre::Radian &pitch, const Ogre::Radian &yaw) { throw NotImplementedError(); }

            std::vector<Tile> &operator[](std::size_t index);
        private:
            int _width;
            int _height;
            ZappyGui::Real _tileWidth;
            ZappyGui::Real _tileHeight;
            std::vector<std::vector<Tile>> _tilemap;
    };
}

#endif
