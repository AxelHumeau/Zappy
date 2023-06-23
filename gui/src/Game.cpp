/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include "Utils.hpp"

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

    void Game::update(SafeQueue<std::string> &requests, float deltaTime) {
        std::map<std::string, std::vector<ZappyGui::Player>>::iterator team;

        for (auto iterator = _teams.begin(); iterator != _teams.end(); iterator++) {
            for (ZappyGui::Player &player : iterator->second) {
                Network::Client::queueRequest(requests, "ppo", { std::to_string(player.getId()) });
            }
        }
    }


    void Game::_updatePlayerPosition(Player &player ) {
        if (player.getPosition() == player.targetMovePosition)
            return;
        Vector3 newPos = player.getPosition();
        newPos = lerp(player.startMovePosition, player.targetMovePosition, player.actionElapsedTime);
        player.setPosition(newPos.x, newPos.y, newPos.z);
        if (player.getPosition().distance(player.startMovePosition) >= player.startMovePosition.distance(player.targetMovePosition) || player.actionElapsedTime >= 1.0f) {
            player.setPosition(player.targetMovePosition.x, player.targetMovePosition.y, player.targetMovePosition.z);
            player.actionElapsedTime = 0.0f;
            player.actionType = ActionType::IDLE;
        }
    }

    void Game::_updatePlayerRotation(Player &player) {
        if (player.getOrientation().getYaw().valueDegrees() == player.targetRotateAngle)
            return;
        Real newAngle = lerpReal(player.startRotateAngle, player.targetRotateAngle, player.actionElapsedTime);
        player.setOrientation(Ogre::Quaternion(Ogre::Degree(newAngle), Vector3(0, 1, 0)));

        if (player.actionElapsedTime >= 1.0f) {
            player.setOrientation(Ogre::Quaternion(Ogre::Degree(player.targetRotateAngle), Vector3(0, 1, 0)));
            player.actionElapsedTime = 0.0f;
            player.actionType = ActionType::IDLE;
        }
    }

    void Game::updatePlayers(float deltaTime) {
        std::map<std::string, std::vector<ZappyGui::Player>>::iterator team;

        for (auto iterator = _teams.begin(); iterator != _teams.end(); iterator++) {
            for (ZappyGui::Player &player : iterator->second) {
                player.actionElapsedTime += deltaTime / player.actionTimeDuration;
                if (player.actionType == ActionType::MOVE)
                    _updatePlayerPosition(player);
                if (player.actionType == ActionType::ROTATE)
                    _updatePlayerRotation(player);
            }
        }
    }
}
