/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** smg
*/

#include "Gui.hpp"

void ZappyGui::smg(ZappyGui::Gui &gui, std::vector<std::string> args) {
    if (args.size() != 1)
        return;
    std::cout << "- Message recived from the server: \"" << args[0] << "\"" << std::endl;
}
