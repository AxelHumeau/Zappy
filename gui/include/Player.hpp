/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_
    #include "GameObject.hpp"
    #include "Tilemap.hpp"

namespace ZappyGui {

    enum Orientation {
        North = 1,
        East = 2,
        South = 3,
        West = 4
    };

    Real facingToAngle(const size_t orientation);

    enum ActionType {
        IDLE,
        MOVE,
        ROTATE
    };

    class Player : public GameObject {
        public:
            Player(std::shared_ptr<Ogre::SceneManager> sceneManager, const std::string &meshName, std::size_t id);
            ~Player() = default;

            size_t getId() const { return _id; }

            void setMapPosition(std::shared_ptr<ZappyGui::Tilemap> tilemap, size_t x, size_t y);
            void setLevel(size_t level) { _level = level; }
            void setFacing(size_t orientation);
            std::size_t getInventoryAmount(const ResourceType &resourceType);
            void setInventoryAmount(const ResourceType &resourceType, std::size_t amount);
            Orientation getFacing() const { return _orientation; }

            Vector3 _startingPoint;
            Real _startingAngle;

            Vector3 _moveTarget;
            Real _targetFacing;

            Real _timeForAction;
            Real _actionTimer;
            ActionType _actionType;
        private:
            std::size_t _id;
            Vector2i _mapPosition;
            size_t _level;
            Orientation _orientation;
            std::unordered_map<ResourceType, std::size_t> _inventory;
    };
}

#endif
