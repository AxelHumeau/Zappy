/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** quit
*/

#include "Gui.hpp"

void ZappyGui::quit(ZappyGui::Gui &gui, std::vector<std::string> args) {
    gui.setDone(true);
}
