/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** bct
*/

#include "Gui.hpp"

void ZappyGui::bct(ZappyGui::Gui &gui, std::vector<std::string> args) {
    std::vector<std::size_t> values;

    if (args.size() != 9)
        return;
    values = gui.convertArgsToSize_t(args);
    if (values.size() != 9)
        return;

    std::shared_ptr<ZappyGui::Tilemap> tilemap = gui.getTilemap();
    std::size_t x = values[0];
    std::size_t y = values[1];
    try {
        tilemap->operator[](y)[x].setResourceAmount(ZappyGui::ResourceType::Food, values[2]);
        tilemap->operator[](y)[x].setResourceAmount(ZappyGui::ResourceType::Linemate, values[3]);
        tilemap->operator[](y)[x].setResourceAmount(ZappyGui::ResourceType::Deraumere, values[4]);
        tilemap->operator[](y)[x].setResourceAmount(ZappyGui::ResourceType::Sibur, values[5]);
        tilemap->operator[](y)[x].setResourceAmount(ZappyGui::ResourceType::Mendiane, values[6]);
        tilemap->operator[](y)[x].setResourceAmount(ZappyGui::ResourceType::Phiras, values[7]);
        tilemap->operator[](y)[x].setResourceAmount(ZappyGui::ResourceType::Thystame, values[8]);
    } catch (ZappyGui::IndexOutOfBoundsError const &e) {
        return;
    }
}
