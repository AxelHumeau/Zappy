/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ppo
*/

#include "Gui.hpp"

void ZappyGui::updatePlayerPosition(Player &player, Gui &gui, std::vector<std::size_t> values) {

    Vector3 newTarget = gui.getTilemap()->getPositionOnTile(values[1], values[2]);
    if (player.targetMovePosition != newTarget) {
        player.setPosition(player.targetMovePosition.x, player.targetMovePosition.y, player.targetMovePosition.z);
        player.targetMovePosition = newTarget;
        player.actionType = ActionType::MOVE;
        player.actionTimeDuration = 7.0f / static_cast<float>(gui.getTimeUnit()) * 0.95f;
        player.startMovePosition = player.getPosition();
        player.actionElapsedTime = 0.0f;
    }
}

void ZappyGui::updatePlayerRotation(Player &player, Gui &gui, std::vector<std::size_t> values) {
        Real newTargetAngle = player.targetRotateAngle;
        if (player.getFacing() == values[3])
            return;
        if (player.getFacing() == Orientation::North && values[3] == Orientation::West)
            newTargetAngle = 90;
        if (player.getFacing() == Orientation::North && values[3] == Orientation::East)
            newTargetAngle = -90;
        if (player.getFacing() == Orientation::West && values[3] == Orientation::South)
            newTargetAngle = 180;
        if (player.getFacing() == Orientation::West && values[3] == Orientation::North)
            newTargetAngle = 0;
        if (player.getFacing() == Orientation::South && values[3] == Orientation::East) {
            player.setOrientation(Ogre::Quaternion(Ogre::Degree(-179), Vector3(0, 1, 0)));
            newTargetAngle = -90;
        }
        if (player.getFacing() == Orientation::South && values[3] == Orientation::West) {
            newTargetAngle = 90;
            player.setOrientation(Ogre::Quaternion(Ogre::Degree(179), Vector3(0, 1, 0)));
        }
        if (player.getFacing() == Orientation::East && values[3] == Orientation::North)
            newTargetAngle = 0;
        if (player.getFacing() == Orientation::East && values[3] == Orientation::South)
            newTargetAngle = -180;

        if (player.targetRotateAngle != newTargetAngle) {
            player.targetRotateAngle = newTargetAngle;
            player.setFacing(values[3]);
            player.actionType = ActionType::ROTATE;
            player.actionTimeDuration = 7.0f / static_cast<float>(gui.getTimeUnit()) * 0.95f;
            player.startRotateAngle = player.getOrientation().getYaw().valueDegrees();
            player.actionElapsedTime = 0.0f;
        }
}

void ZappyGui::ppo(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 4)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 4)
        return;
    try {
        Player &player = gui.getGame().getPlayer(values[0]);
        updatePlayerPosition(player, gui, values);
        updatePlayerRotation(player, gui, values);
    } catch (ZappyGui::PlayerUndifinedError const &e) {
        return;
    }
}
