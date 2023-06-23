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

    TeamUndefinedError::TeamUndefinedError(std::string teamName)
    : message("Undefined team: \"" + teamName + "\"") {}
    char const *TeamUndefinedError::what() const noexcept { return message.c_str(); }

    PlayerUndefinedError::PlayerUndefinedError(std::size_t playerId)
    : message("Undefined player: \"" + std::to_string(playerId) + "\"") {}
    char const *PlayerUndefinedError::what() const noexcept { return message.c_str(); }

    void Game::addTeam(std::string teamName) {
        if (_teams.find(teamName) == _teams.end())
            _teams[teamName] = {};
    }

    std::list<ZappyGui::Player> &Game::getTeam(std::string teamName) {
        if (_teams.find(teamName) == _teams.end())
            throw TeamUndefinedError(teamName);
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
        throw PlayerUndefinedError(playerId);
    }

    void Game::removePlayer(size_t playerId) {
        for (auto iterator = _teams.begin(); iterator != _teams.end(); iterator++)
            iterator->second.remove_if([playerId](ZappyGui::Player &player){ return player.getId() == playerId; });
        throw PlayerUndefinedError(playerId);
    }

    void Game::update(SafeQueue<std::string> &requests) {
        std::map<std::string, std::vector<ZappyGui::Player>>::iterator team;

        for (auto iterator = _teams.begin(); iterator != _teams.end(); iterator++) {
            for (ZappyGui::Player &player : iterator->second) {
                Network::Client::queueRequest(requests, "ppo", { std::to_string(player.getId()) });
            }
        }
    }
}
