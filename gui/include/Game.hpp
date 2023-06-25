/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_
    #include <vector>
    #include <list>
    #include <map>
    #include <string>
    #include "Player.hpp"
    #include "SafeQueue.hpp"
    #include "Client.hpp"

namespace ZappyGui {

    /**
     * @brief
     * TeamUndefinedError Class Error
     * Error thrown when trying to get a team that does not exist.
     */
    class TeamUndefinedError : public std::exception {
        public:
            TeamUndefinedError(std::string teamName);
            ~TeamUndefinedError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * PlayerUndefinedError Class Error
     * Error thrown when trying to get a player that does not exist.
     */
    class PlayerUndefinedError : public std::exception {
        public:
            PlayerUndefinedError(std::size_t playerId);
            ~PlayerUndefinedError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    class Game {
        public:
            Game() = default;
            ~Game() = default;

            /// @brief get the number of teams
            /// @return a size_t of the number of teams
            std::size_t getNbTeams() const { return _teams.size(); }
            /// @brief add a team with the name gived in parameters
            /// @param teamName name of the team
            void addTeam(std::string teamName);
            /// @brief get a team by its name
            /// @param teamName the name of the team to retrieve
            /// @return remove the team or trow TeamUndefinedError if the team does not exit
            std::list<ZappyGui::Player> &getTeam(std::string teamName);
            /// @brief get a player by its id
            /// @param playerId id of the player to get
            /// @return a reference to the player or PlayerUndefinedError if the player does not exist
            Player &getPlayer(size_t playerId);
            /// @brief remove a player by its id or throw PlayerUndefinedError if the player does not exist
            /// @param playerId the id of the player to delete
            void removePlayer(size_t playerId);
            /// @brief send to the server all the request required for sync update
            /// @param requests Safequeue containing all the requests to send
            /// @param deltaTime time elapsed from the last frame
            void update(SafeQueue<std::string> &requests, float deltaTime);
            /// @brief updates player position and rotation based on the delta time
            /// @param deltaTime time elapsed from the last frame
            void updatePlayers(float deltaTime);
            std::map<std::string, std::list<ZappyGui::Player>> &getTeams() { return _teams; };
        private:
            /// @brief Update the player position smoothly
            /// @param player the player to update
            void _updatePlayerPosition(Player &player );
            /// @brief Update the player rotation smoothly
            /// @param player the player to update
            void _updatePlayerRotation(Player &player );

            std::map<std::string, std::list<ZappyGui::Player>> _teams;
    };
}

#endif
