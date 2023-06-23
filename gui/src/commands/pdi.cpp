/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pdi
*/

#include "Gui.hpp"

void ZappyGui::pdi(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 1)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 1)
        return;
    try {
        gui.getGame().removePlayer(values[0]);
    } catch (ZappyGui::PlayerUndefinedError const &e) {
        return;
    }
}
