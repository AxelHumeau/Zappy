/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tna
*/

#include "Gui.hpp"

void ZappyGui::tna(ZappyGui::Gui &gui, std::vector<std::string> args) {
    if (args.size() != 1)
        return;
    gui.getGame().addTeam(args[0]);
}
