/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** enw
*/

#include "Gui.hpp"

void ZappyGui::enw(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 4)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 4)
        return;
    std::cout << "- (" << values[1] << ") has layed the egg (" << values[0] << ")";
    std::cout << " in (x: " << values[2] << ", y: " << values[3] << ")" << std::endl;
}
