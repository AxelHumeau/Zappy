/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pex
*/

#include "Gui.hpp"

void ZappyGui::pex(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 1)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 1)
        return;
    std::cout << "- (" << values[0] << ") is expulsing someones" << std::endl;
}
