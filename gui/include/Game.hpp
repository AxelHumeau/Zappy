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

            std::size_t getNbTeams() const { return _teams.size(); }
            void addTeam(std::string teamName);
            std::list<ZappyGui::Player> &getTeam(std::string teamName);
            Player &getPlayer(size_t playerId);
            void removePlayer(size_t playerId);
            void update(SafeQueue<std::string> &requests);
            std::map<std::string, std::list<ZappyGui::Player>> &getTeams() { return _teams; };

        private:
            std::map<std::string, std::list<ZappyGui::Player>> _teams;
    };
}

#endif
