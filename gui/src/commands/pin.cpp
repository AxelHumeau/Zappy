/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** *
*/

#include "Gui.hpp"

void ZappyGui::pin(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 10)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 10)
        return;
    try {
        ZappyGui::Player &player = gui.getGame().getPlayer(values[0]);
        player.setInventoryAmount(ZappyGui::ResourceType::Food, values[3]);
        player.setInventoryAmount(ZappyGui::ResourceType::Linemate, values[4]);
        player.setInventoryAmount(ZappyGui::ResourceType::Deraumere, values[5]);
        player.setInventoryAmount(ZappyGui::ResourceType::Sibur, values[6]);
        player.setInventoryAmount(ZappyGui::ResourceType::Mendiane, values[7]);
        player.setInventoryAmount(ZappyGui::ResourceType::Phiras, values[8]);
        player.setInventoryAmount(ZappyGui::ResourceType::Thystame, values[9]);
    } catch (ZappyGui::PlayerUndefinedError const &e) {
        return;
    }
}
