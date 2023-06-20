/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** seg
*/

#include "Gui.hpp"

void ZappyGui::seg(ZappyGui::Gui &gui, std::vector<std::string> args) {
    if (args.size() != 1)
        return;
    std::cout << "- End of game, team " << args[0] << "wins !" << std::endl;
}
