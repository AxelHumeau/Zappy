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
    #include "SafeQueue.hpp"
    #include <vector>

namespace ZappyGui {
    class Tilemap : public AGameObject {
        public:
            Tilemap(std::shared_ptr<Ogre::SceneManager> sceneManager, int width, int height);
            ~Tilemap() {};
            /// @brief set the spacing between tiles of the tilemap
            /// @param width spacing
            /// @param height spacing
            void setTileSize(ZappyGui::Real width, ZappyGui::Real height, ZappyGui::Real depth);
            /// @brief return the size of the tiles in the tilemap
            /// @return a Vector2 containing the width and the height of the tiles
            Vector3 getTileSize() { return _tileSize; }
            /// @brief return the size of the tilemap
            /// @return a Vector2i containing the width and the height of tilemap
            Vector2i getSize() { return Vector2i(_width, _height); }

            void placeGameObjectOnTile(ZappyGui::Tile &tile, ZappyGui::GameObject &obj);

            /// @brief Not implemented !
            /// @return throw an NotImplementedError
            void lookAt(
                const Ogre::Vector3 &targetPoint,
                Ogre::Node::TransformSpace relativeTo,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) { throw NotImplementedError(); }
            /// @brief Not implemented !
            /// @return throw an NotImplementedError
            void setDirection(
                Ogre::Real x,
                Ogre::Real y,
                Ogre::Real z,
                Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT,
                const Ogre::Vector3 &localDirectionVector = Ogre::VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z
            ) { throw NotImplementedError(); }
            /// @brief Not implemented !
            /// @return throw an NotImplementedError
            void setRotation(const Ogre::Radian &roll, const Ogre::Radian &pitch, const Ogre::Radian &yaw) { throw NotImplementedError(); }
            void update(SafeQueue<std::string> &requests);

            /// @brief operator[] overload to access the _tilemap
            /// @param index index of the the tilemap row to get
            /// @return row of the tilemap at index | throw an IndexOutOfBoundsError if the index is out of bounds
            std::vector<Tile> &operator[](std::size_t index);
        private:
            int _width;
            int _height;
            ZappyGui::Vector3 _tileSize;
            std::vector<std::vector<Tile>> _tilemap;
    };
}

#endif
