/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pnw
*/

#include "Gui.hpp"

void ZappyGui::pnw(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 6)
        return;
    values = gui.convertArgsToSize_t(args, 0, args.size() - 2);
    if (values.size() != 5)
        return;
    try {
        std::list<ZappyGui::Player> &team = gui.getGame().getTeam(args[5]);
        team.emplace_back(gui.getRenderer().getSceneManager(), "Mathias.mesh", values[0]);
        team.back().setMapPosition(values[1], values[2]);
        team.back().setOrientation(values[3]);
        team.back().setLevel(values[4]);
    } catch (ZappyGui::TeamUndifinedError const &e) {
        return;
    }
}
