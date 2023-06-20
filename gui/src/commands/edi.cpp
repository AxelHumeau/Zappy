/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** edi
*/

#include "Gui.hpp"

void ZappyGui::edi(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 1)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 1)
        return;
    std::cout << "- The egg (" << values[0] << ") is dead" << std::endl;
}
