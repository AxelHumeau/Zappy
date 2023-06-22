/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ppo
*/

#include "Gui.hpp"

void ZappyGui::ppo(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 4)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 4)
        return;
    try {
        Player &player = gui.getGame().getPlayer(values[0]);
        // player.setMapPosition(gui.getTilemap(), values[1], values[2]);
        ZappyGui::Vector3 newTarget = gui.getTilemap()->getPositionOnTile(values[1], values[2]);
        if (player._moveTarget != newTarget) {
            // nombre joueur sur tile
            player.setPosition(player._moveTarget.x, player._moveTarget.y, player._moveTarget.z);
            player._moveTarget = newTarget;
            player._actionType = ActionType::MOVE;
            player._timeForAction = 7.0f / static_cast<float>(gui.getTimeUnit()) * 0.95f;
            player._startingPoint = player.getPosition();
            player._actionTimer = 0.0f;
        }

        Real newTargetAngle = player._targetFacing;
        if (player.getFacing() == Orientation::North && values[3] == Orientation::West)
            newTargetAngle -= 90;
        if (player.getFacing() == Orientation::North && values[3] == Orientation::East)
            newTargetAngle += 90;

        if (player.getFacing() == Orientation::East && values[3] == Orientation::North)
            newTargetAngle -= 90;
        if (player.getFacing() == Orientation::East && values[3] == Orientation::South)
            newTargetAngle += 90;

        if (player.getFacing() == Orientation::South && values[3] == Orientation::East)
            newTargetAngle -= 90;
        if (player.getFacing() == Orientation::South && values[3] == Orientation::West)
            newTargetAngle += 90;

        if (player.getFacing() == Orientation::West && values[3] == Orientation::South)
            newTargetAngle -= 90;
        if (player.getFacing() == Orientation::West && values[3] == Orientation::North)
            newTargetAngle += 90;

        if (newTargetAngle == 360) {
            newTargetAngle = 0;
            player.setOrientation(Ogre::Quaternion(Ogre::Degree(player.getOrientation().getYaw().valueDegrees() - 360), Vector3(0, 1, 0)));
        }


        // std::cout << player.getOrientation().getYaw().valueDegrees() << " => " << newTargetAngle << std::endl;

        if (player._targetFacing != newTargetAngle) {
            std::cout << "Targeted facing: " << player._targetFacing << std::endl;
            player._targetFacing = newTargetAngle;
            // player.setOrientation(Ogre::Quaternion(Ogre::Degree(player._targetFacing), Vector3(0, 1, 0)));
            player.setFacing(values[3]);
            // player.setOrientation(Ogre::Quaternion(Ogre::Degree(player._targetFacing), Vector3(0, 1, 0)));
            // player.setFacing(values[3]);
            // player._targetFacing  = newTargetAngle;
            // player._actionType = ActionType::ROTATE;
            // player._timeForAction = 7.0f / static_cast<float>(gui.getTimeUnit()) * 0.95f;
            // player._startingAngle = player.getOrientation().getYaw().valueDegrees();
            // player._actionTimer = 0.0f;
        }
    } catch (ZappyGui::PlayerUndifinedError const &e) {
        return;
    }
}
