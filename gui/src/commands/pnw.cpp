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
        team.emplace_back(gui.getRenderer().getSceneManager(), "Washy.mesh", values[0]);

        ZappyGui::Vector3 finalPosition;
        std::shared_ptr<ZappyGui::Tilemap> tilemap = gui.getTilemap();
        finalPosition = tilemap->getPositionOnTile(values[1], values[2]);

        team.back().setPosition(finalPosition.x, finalPosition.y, finalPosition.z);
        team.back()._moveTarget = finalPosition;
        team.back().setFacing(values[3]);
        team.back()._targetFacing = team.back().getOrientation().getYaw().valueDegrees();
        std::cout << "Player starting " << team.back()._orientation << std::endl;
        // team.back()._targetFacing = team.back().getOrientation().getYaw().valueDegrees();
        team.back().setLevel(values[4]);
    } catch (ZappyGui::TeamUndifinedError const &e) {
        return;
    }
}
