/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_
    #include "GameObject.hpp"
    #include <map>

namespace ZappyGui {

    /**
     * @brief
     * TileNoGameobjectBoundError Class Error
     * Error thrown when trying to get a Tile Gameobject that is not bind.
     */
    class TileNoGameobjectBoundError : public std::exception {
        public:
            TileNoGameobjectBoundError();
            ~TileNoGameobjectBoundError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    class Tile {
        public:
            Tile(std::shared_ptr<Ogre::SceneManager> sceneManager, int x, int y);
            ~Tile() {};
            /// @brief get the position of the tile in the tilemap
            /// @return Vector2i containing the position of the tile in the tilemap
            ZappyGui::Vector2i getPosition() const { return ZappyGui::Vector2i(_x, _y); }
            /// @brief bind the given gameobject to the tile
            /// @param gameObject to bind to the tile
            void bindGameObject(std::shared_ptr<ZappyGui::GameObject> gameObject) { _gameobject = gameObject; }
            /// @brief return the gameobject bound to the tile
            /// @return the gameobject bound or throw an TileNoGameobjectBoundError if no gameobject is bound
            ZappyGui::GameObject &getGameobject();
            /// @brief get the amount of the given resourceType
            /// @param resourceType to get the amount
            /// @return the amount of the given resourceType or throw an TileUndefinedResourceTypeError
            std::size_t getResourceAmount(const ResourceType &resourceType);
            /// @brief set the amount of the given resourceType of the tile and update the visualization
            /// @param resourceType name of the resource
            /// @param amount amount of the resource
            void setResourceAmount(const ResourceType &resourceType, std::size_t amount);
            /// @brief set the size of the tile (spacing between all the tiles)
            /// @param tileSize Vector3 of the size
            void setTileSize(ZappyGui::Vector3 tileSize) { _tileSize = tileSize; }
            /// @brief set the position of the tilemap saved by the tile to be placed correctly
            /// @param tilemapOrigin position of the tilemap
            void setTilemapOrigin(ZappyGui::Vector3 tilemapOrigin) { _tilemapOrigin = tilemapOrigin; }

        private:
            std::shared_ptr<Ogre::SceneManager> _sceneManager;
            int _x;
            int _y;
            ZappyGui::Vector3 _tileSize;
            ZappyGui::Vector3 _tilemapOrigin;
            std::shared_ptr<ZappyGui::GameObject> _gameobject = nullptr;
            std::map<ResourceType, std::pair<std::size_t, std::list<ZappyGui::GameObject>>> _resources;
            /// @brief spawn a resource visualization gameObject on the tile at a random position
            /// @param resourceList list to add the visualization gameObject
            /// @param mesh name of the gameObject mesh
            /// @param precision number of posible positions in the available space in the tile
            /// @param availableSpace factor to reduce the area available for spawning
            void _placeResourceOnTile(std::list<ZappyGui::GameObject> &resourceList, std::string mesh, int precision = 100, float availableSpace = 0.70f);
            /// @brief update the tile visualisation gameObject according to its resources
            void _updateResourceOnTile();
    };
}

#endif
