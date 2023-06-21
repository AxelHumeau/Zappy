/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pic
*/

#include "Gui.hpp"

void ZappyGui::pic(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() < 4)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() < 4)
        return;
    std::cout << "- (" << values[3] << ") start an incantation to the level " << values[2];
    std::cout << " in (x: " << values[0] << ", y:" << values[1] << ")";
    if (values.size() > 4) {
        std::cout << " with (";
        for (std::size_t i = 5; i < values.size(); i++) {
            std::cout << values[i];
            if (i != values.size() - 1)
                std::cout << ", ";
        }
        std::cout << ")";
    }
    std::cout << std::endl;
}
