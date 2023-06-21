/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ebo
*/

#include "Gui.hpp"

void ZappyGui::ebo(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 1)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 1)
        return;
    std::cout << "- A new player as hatched from the egg (" << values[0] << ")" << std::endl;
}
