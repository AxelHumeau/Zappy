/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ppo
*/

#include "Gui.hpp"

void ZappyGui::ppo(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 4)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 4)
        return;
    try {
        Player &player = gui.getGame().getPlayer(values[0]);
        // player.setMapPosition(gui.getTilemap(), values[1], values[2]);
        ZappyGui::Vector3 newTarget = gui.getTilemap()->getPositionOnTile(values[1], values[2]);
        if (player._moveTarget != newTarget) {
            player.setPosition(player._moveTarget.x, player._moveTarget.y, player._moveTarget.z);
            player._moveTarget = newTarget;
            player._timeForAction = 7.0f / static_cast<float>(gui.getTimeUnit()) * 0.95f;
            player._startingPoint = player.getPosition();
            player._actionTimer = 0.0f;
        }
        std::cout << "[" << player.getPosition().x << "][" << player.getPosition().y << "][" << player.getPosition().z << "] => ";
        std::cout << "[" << player._moveTarget.x << "][" << player._moveTarget.y << "][" << player._moveTarget.z << "]" << std::endl;

        player.setFacing(values[3]);
    } catch (ZappyGui::PlayerUndifinedError const &e) {
        return;
    }
}
