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
    /**
     * @brief
     * TileUndifinedResourceTypeError Class Error
     * Error thrown when trying to get a Tile Gameobject that is not bind.
     */
    class TileUndifinedResourceTypeError : public std::exception {
        public:
            TileUndifinedResourceTypeError(std::string resourceType);
            ~TileUndifinedResourceTypeError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    class Tile {
        public:
            Tile(int x, int y);
            ~Tile() {};
            std::pair<int, int> getPosition() const { return std::pair<int, int>(_x, _y); }
            void bindGameObject(std::shared_ptr<ZappyGui::GameObject> gameObject) { _gameobject = gameObject; }
            ZappyGui::GameObject const &getGameobject();
            std::size_t getResourceAmount(const std::string &resourceType);

        private:
            int _x;
            int _y;
            std::shared_ptr<ZappyGui::GameObject> _gameobject = nullptr;
            std::unordered_map<std::string, std::size_t> _resources;
    };
}

#endif
