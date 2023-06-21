/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>
#include <algorithm>

namespace ZappyGui {

    TeamUndifinedError::TeamUndifinedError(std::string teamName)
    : message("Undifined team: \"" + teamName + "\"") {}
    char const *TeamUndifinedError::what() const noexcept { return message.c_str(); }

    PlayerUndifinedError::PlayerUndifinedError(std::size_t playerId)
    : message("Undifined player: \"" + std::to_string(playerId) + "\"") {}
    char const *PlayerUndifinedError::what() const noexcept { return message.c_str(); }

    void Game::addTeam(std::string teamName) {
        if (_teams.find(teamName) == _teams.end())
            _teams[teamName] = {};
    }

    std::list<ZappyGui::Player> &Game::getTeam(std::string teamName) {
        if (_teams.find(teamName) == _teams.end())
            throw TeamUndifinedError(teamName);
        return _teams[teamName];
    }

    Player &Game::getPlayer(size_t playerId) {
	    std::map<std::string, std::list<ZappyGui::Player>>::iterator iterator = _teams.begin();
        while (iterator != _teams.end()) {
            for (ZappyGui::Player &player : iterator->second) {
                if (player.getId() == playerId)
                    return player;
            }
            iterator++;
        }
        throw PlayerUndifinedError(playerId);
    }

    void Game::removePlayer(size_t playerId) {
        for (auto iterator = _teams.begin(); iterator != _teams.end(); iterator++)
            iterator->second.remove_if([playerId](ZappyGui::Player &player){ return player.getId() == playerId; });
        throw PlayerUndifinedError(playerId);
    }

    void Game::update(SafeQueue<std::string> &requests) {
        std::map<std::string, std::vector<ZappyGui::Player>>::iterator team;

        for (auto iterator = _teams.begin(); iterator != _teams.end(); iterator++) {
            for (ZappyGui::Player &player : iterator->second) {
                // Network::Client::queueRequest(requests, "ppo", { std::to_string(player.getId()) });
            }
        }
    }
}
