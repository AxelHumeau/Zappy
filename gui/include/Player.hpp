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

            void setMapPosition(size_t x, size_t y);
            void setLevel(size_t level) { _level = level; }
            void setFacingAndPosition(size_t orientation);
            void setFacing(size_t orientation);
            std::size_t getInventoryAmount(const ResourceType &resourceType);
            void setInventoryAmount(const ResourceType &resourceType, std::size_t amount);
            void setTeam(std::string team) { _team = team; };

            std::string getTeam() const { return _team; };
            std::size_t getLevel() const { return _level; };
            ZappyGui::Vector2i getMapPosition() const { return _mapPosition; };
            Orientation getFacing() const { return _facing; }

            Vector3 startMovePosition;
            Vector3 targetMovePosition;
            Real startRotateAngle;
            Real targetRotateAngle;
            Real actionTimeDuration;
            Real actionElapsedTime;
            ActionType actionType;
        private:
            std::size_t _id;
            std::string _team;
            ZappyGui::Vector2i _mapPosition;
            size_t _level;
            Orientation _facing;
            std::unordered_map<ResourceType, std::size_t> _inventory;
    };
}

#endif
