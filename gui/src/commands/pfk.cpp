/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pfk
*/

#include "Gui.hpp"

void ZappyGui::pfk(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 1)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 1)
        return;
    std::cout << "- (" << values[0] << ") is laying an egg" << std::endl;
}
