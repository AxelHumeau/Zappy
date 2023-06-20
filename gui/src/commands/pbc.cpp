/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pbc
*/

#include "Gui.hpp"

void ZappyGui::pbc(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 2)
        return;
    values = gui.convertArgsToSize_t(args, 0, 0);
    if (values.size() != 1)
        return;
    std::cout << "- (" << values[0] << ") shouted \"" << args[1] << "\"" << std::endl;
}
