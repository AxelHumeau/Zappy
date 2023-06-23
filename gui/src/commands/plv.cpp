/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** plv
*/

#include "Gui.hpp"

void ZappyGui::plv(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 2)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 2)
        return;
    try {
        ZappyGui::Player &player = gui.getGame().getPlayer(values[0]);
        player.setLevel(values[1]);
    } catch (ZappyGui::PlayerUndefinedError const &e) {
        return;
    }
}
