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

        if (Orientation(player._orientation) == values[3])
            return;

        // if (player._orientation == Orientation::North && values[3] == Orientation::East)
        //     newTargetAngle = 270;
        // if (player._orientation == Orientation::North && values[3] == Orientation::West)
        //     newTargetAngle = 90;

        // if (player._orientation == Orientation::East && values[3] == Orientation::South)
        //     newTargetAngle = 180;
        // if (player._orientation == Orientation::East && values[3] == Orientation::North)
        //     newTargetAngle = 0;

        // if (player._orientation == Orientation::South && values[3] == Orientation::West)
        //     newTargetAngle = 90;
        // if (player._orientation == Orientation::South && values[3] == Orientation::East)
        //     newTargetAngle = 270;

        // if (player._orientation == Orientation::West && values[3] == Orientation::North)
        //     newTargetAngle = 0;
        // if (player._orientation == Orientation::West && values[3] == Orientation::South)
        //     newTargetAngle = 180;

        if (player._orientation == Orientation::North && values[3] == Orientation::West)
            newTargetAngle = 90;
        if (player._orientation == Orientation::North && values[3] == Orientation::East)
            newTargetAngle = -90;

        if (player._orientation == Orientation::West && values[3] == Orientation::South)
            newTargetAngle = 180;
        if (player._orientation == Orientation::West && values[3] == Orientation::North)
            newTargetAngle = 0;

        if (player._orientation == Orientation::South && values[3] == Orientation::East)
            newTargetAngle = -90;
        if (player._orientation == Orientation::South && values[3] == Orientation::West)
            newTargetAngle = 90;

        if (player._orientation == Orientation::East && values[3] == Orientation::North)
            newTargetAngle = 0;
        if (player._orientation == Orientation::East && values[3] == Orientation::South)
            newTargetAngle = -180;

        // if (values[3] == Orientation::North)
        //     newTargetAngle = 0.0f;
        // if (values[3] == Orientation::East)
        //     newTargetAngle = 270.0f;
        // if (values[3] == Orientation::South)
        //     newTargetAngle = 180.0f;
        // if (values[3] == Orientation::West)
        //     newTargetAngle = 90.0f;

        // if (newTargetAngle == -360 || newTargetAngle == 360) {
        //     if (newTargetAngle == 360)
        //         player.setOrientation(Ogre::Quaternion(Ogre::Degree(player.getOrientation().getYaw().valueDegrees() - 360), Vector3(0, 1, 0)));
        //     if (newTargetAngle == -360)
        //         player.setOrientation(Ogre::Quaternion(Ogre::Degree(player.getOrientation().getYaw().valueDegrees() + 360), Vector3(0, 1, 0)));
        //     newTargetAngle = 0;
        //     player._startingAngle = 0;
        // }

        std::cout << player.getOrientation().getYaw().valueDegrees() << " => " << newTargetAngle << std::endl;
        if (player._targetFacing != newTargetAngle) {
            player._targetFacing = newTargetAngle;
            player._orientation = Orientation(values[3]);
            player._actionType = ActionType::ROTATE;
            player._timeForAction = 7.0f / static_cast<float>(gui.getTimeUnit()) * 0.95f;
            player._startingAngle = player.getOrientation().getYaw().valueDegrees();
            player._actionTimer = 0.0f;
        }
    } catch (ZappyGui::PlayerUndifinedError const &e) {
        return;
    }
}
