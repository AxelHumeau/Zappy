/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pdr
*/

#include "Gui.hpp"

void ZappyGui::pdr(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 2)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 2)
        return;
    std::cout << "- (" << values[0] << ") dropped an " << ZappyGui::ResourceType(values[1]) << std::endl;
}
