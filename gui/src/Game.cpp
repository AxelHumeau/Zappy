/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>

namespace ZappyGui {

    TeamUndifinedError::TeamUndifinedError(std::string teamName)
    : message("Undifined team: \"" + teamName + "\"") {}
    char const *TeamUndifinedError::what() const noexcept { return message.c_str(); }

    PlayerUndifinedError::PlayerUndifinedError(std::size_t playerId)
    : message("Undifined team: \"" + std::to_string(playerId) + "\"") {}
    char const *PlayerUndifinedError::what() const noexcept { return message.c_str(); }

    void Game::addTeam(std::string teamName) {
        if (_teams.find(teamName) == _teams.end())
            _teams[teamName] = {};
    }

    std::vector<ZappyGui::Player> &Game::getTeam(std::string teamName) {
        if (_teams.find(teamName) == _teams.end())
            throw TeamUndifinedError(teamName);
        return _teams[teamName];
    }

    Player &Game::getPlayer(size_t playerId) {
	    std::map<std::string, std::vector<ZappyGui::Player>>::iterator iterator = _teams.begin();
        while (iterator != _teams.end()) {
            std::vector<ZappyGui::Player> players = iterator->second;
            for (int i = 0; i < players.size(); i++) {
                if (players[i].getId() == playerId)
                    return players[i];
            }
            iterator++;
        }
        throw PlayerUndifinedError(playerId);
    }

    void Game::removePlayer(size_t playerId) {
	    std::map<std::string, std::vector<ZappyGui::Player>>::iterator iterator = _teams.begin();
        while (iterator != _teams.end()) {
            std::vector<ZappyGui::Player> &players = iterator->second;
            for (int i = 0; i < players.size(); i++) {
                if (players[i].getId() == playerId) {
                    players.erase(players.begin() + i);
                }
            }
            iterator++;
        }
        throw PlayerUndifinedError(playerId);
    }
}
