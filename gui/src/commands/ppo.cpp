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
        player.setMapPosition(values[1], values[2]);
        player.setOrientation(values[3]);
    } catch (ZappyGui::PlayerUndifinedError const &e) {
        return;
    }
}
