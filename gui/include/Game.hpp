/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_
    #include <vector>
    #include <map>
    #include <string>
    #include "Player.hpp"

namespace ZappyGui {

    /**
     * @brief
     * TeamUndifinedError Class Error
     * Error thrown when trying to get a team that does not exist.
     */
    class TeamUndifinedError : public std::exception {
        public:
            TeamUndifinedError(std::string teamName);
            ~TeamUndifinedError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * PlayerUndifinedError Class Error
     * Error thrown when trying to get a player that does not exist.
     */
    class PlayerUndifinedError : public std::exception {
        public:
            PlayerUndifinedError(std::size_t playerId);
            ~PlayerUndifinedError() = default;
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    class Game {
        public:
            Game() = default;
            ~Game() = default;

            std::size_t getNbTeams() const { return _teams.size(); }
            void addTeam(std::string teamName);
            std::vector<ZappyGui::Player> &getTeam(std::string teamName);
            Player &getPlayer(size_t playerId);
            void removePlayer(size_t playerId);

        private:
            std::map<std::string, std::vector<ZappyGui::Player>> _teams;
    };
}

#endif
