/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pie
*/

#include "Gui.hpp"

void ZappyGui::pie(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 3)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 3)
        return;
    std::cout << "- Incantation ";
    if (values[2] == 0)
        std::cout << "failed";
    else
        std::cout << "succeded";
    std::cout << " in (x: " << values[0] << ", y: " << values[1] << ")" << std::endl;
}
