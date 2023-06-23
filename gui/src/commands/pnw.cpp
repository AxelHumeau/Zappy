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
        team.back().targetMovePosition = finalPosition;
        team.back().setFacingAndPosition(values[3]);
        team.back().targetRotateAngle = team.back().getOrientation().getYaw().valueDegrees();
        team.back().setLevel(values[4]);
        team.back().setTeam(args[5]);
    } catch (ZappyGui::TeamUndefinedError const &e) {
        return;
    }
}
