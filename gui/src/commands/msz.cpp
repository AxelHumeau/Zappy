/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** msz
*/

#include "Gui.hpp"

void ZappyGui::msz(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;
    std::pair<size_t, size_t> mapSize = gui.getMapSize();

    if (args.size() != 2 || mapSize.first != 0 || mapSize.second != 0)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 2)
        return;
    gui.setMapSize(values[0], values[1]);
}
