/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_
    #include "GameObject.hpp"

namespace ZappyGui {

    enum Orientation {
        North = 1,
        East = 2,
        South = 3,
        West = 4
    };

    class Player : public GameObject {
        public:
            Player(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName, std::size_t id): GameObject(sceneManager, meshName), _id{id} {};
            ~Player() = default;

            size_t getId() const { return _id; }

            void setMapPosition(size_t x, size_t y) { _mapPositionX = x; _mapPositionY = y; }
            void setLevel(size_t level) { _level = level; }
            void setOrientation(size_t orientation);
            void setOrientation(Orientation orientation) { _orientation = orientation; }

        private:
            std::size_t _id;
            size_t _mapPositionX;
            size_t _mapPositionY;
            size_t _level;
            Orientation _orientation;
    };
}

#endif
