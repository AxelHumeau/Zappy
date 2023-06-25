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

            /// @brief return the id of the player
            /// @return size_t id of the player
            size_t getId() const { return _id; }

            /// @brief set the postition of the player in the map (not in the world)
            /// @param x x position
            /// @param y y position
            void setMapPosition(size_t x, size_t y);
            /// @brief set the level of the player
            /// @param level new level to set
            void setLevel(size_t level) { _level = level; }
            /// @brief set the facing of the player and rotate it to the correct angle
            /// @param orientation new orientation to set
            void setFacingAndPosition(size_t orientation);
            /// @brief set only the facing of the player but don't rotate it
            /// @param orientation new orientation to set
            void setFacing(size_t orientation);
            /// @brief get the amount of a specific resource in the player inventory
            /// @param resourceType name of the resource to get the amount
            /// @return the amount of the resource or UndefinedResourceTypeError if the resourceType does not exist
            std::size_t getInventoryAmount(const ResourceType &resourceType);
            /// @brief set the amount of a specific resource in the player inventory
            /// @param resourceType name of the resource to set the amount
            /// @param amount the amount of the resource to set
            /// @return can throw UndefinedResourceTypeError if the resourceType does not exist
            void setInventoryAmount(const ResourceType &resourceType, std::size_t amount);
            /// @brief set the team of the player
            /// @param team name of the team to set
            void setTeam(std::string team) { _team = team; };

            /// @brief get the name of the player team
            /// @return the name of the player team
            std::string getTeam() const { return _team; };
            /// @brief get the level of the player
            /// @return level of the player
            std::size_t getLevel() const { return _level; };
            /// @brief get the player position on the map
            /// @return Vector2i containing the position
            ZappyGui::Vector2i getMapPosition() const { return _mapPosition; };
            /// @brief get the facing of the player
            /// @return orientation of the player
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
