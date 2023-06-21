/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** sst
*/

#include "Gui.hpp"

void ZappyGui::sst(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 1)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 1)
        return;
    gui.setTimeUnit(values[0]);
    std::cout << "- New time unit is " << gui.getTimeUnit() << std::endl;
}
