/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_
    #include "GameObject.hpp"

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
            Tile(int x, int y);
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
            void setResourceAmount(const ResourceType &resourceType, std::size_t amount);

        private:
            int _x;
            int _y;
            std::shared_ptr<ZappyGui::GameObject> _gameobject = nullptr;
            std::unordered_map<ResourceType, std::size_t> _resources;
    };
}

#endif
