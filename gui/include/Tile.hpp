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
    class Tile {
        public:
            Tile(int x, int y): _x{x}, _y{y} {};
            ~Tile() {};
            std::pair<int, int> getPosition() const { return std::pair<int, int>(_x, _y); }
            void setGameObject(ZappyGui::GameObject &gameObject) { _gameobject.reset(&gameObject, ZappyGui::nop{}); }
            std::shared_ptr<ZappyGui::GameObject> getGameobject() { return _gameobject; };

        private:
            int _x;
            int _y;
            std::shared_ptr<ZappyGui::GameObject> _gameobject = nullptr;
    };
}

#endif
