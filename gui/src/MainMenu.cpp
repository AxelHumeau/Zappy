/*
** EPITECH PROJECT, 2023
** MainMenu.cpp
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

void ZappyGui::closeWindow(ZappyGui::Gui &gui)
{
    gui.setDone(true);
}

void ZappyGui::endInitialization(ZappyGui::Gui &gui)
{
    gui.setEndInitialization(true);
}

ZappyGui::MainMenu::MainMenu(std::shared_ptr<Ogre::Overlay> overlay, int width, int height)
{
    static std::size_t index;
    _createBackground(overlay, width, height, index);
    _createLaunch(overlay, width, height, index);
    _createQuit(overlay, width, height, index);
    index++;
}

void ZappyGui::MainMenu::update(ZappyGui::Gui &gui, int x, int y, MouseEvent &event)
{
    if (_launch->update(gui, x, y, event))
        return;
    _quit->update(gui, x, y, event);
}

void ZappyGui::MainMenu::_createBackground(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, std::size_t index)
{
    _bg.reset(new ZappyGui::Panel(overlay, "Background_" + std::to_string(index), false));
    _bg->panelSetDimensions(width, height);
    _bg->panelSetPosition(0, 0);
    _bg->panelSetMaterial("BackgroundMaterial", "Assets");
}

void ZappyGui::MainMenu::_createLaunch(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, std::size_t index)
{
    _launch.reset(new ZappyGui::Button(overlay, "Launch_" + std::to_string(index), "MenuButtonDefault", endInitialization));
    _launch->panelSetDimensions(500, 150);
    _launch->panelSetPosition(width / 2 - 250, height / 2 - 200);
    _launch->setMaterials("MenuButtonDefault", "MenuButtonHover", "MenuButtonClick");

    _launch->addTextArea("Launch_" + std::to_string(index) + "_text", 250, 55, "defaultFont");
    _launch->textSetAlignment("Launch_" + std::to_string(index) + "_text", Ogre::TextAreaOverlayElement::Center);
    _launch->textSetText("Launch_" + std::to_string(index) + "_text", "Launch");
    _launch->textSetCharacterHeight("Launch_" + std::to_string(index) + "_text", 50);
    _launch->textSetColorBottom("Launch_" + std::to_string(index) + "_text", Ogre::ColourValue(0.7, 0.7, 0.7));
    _launch->textSetColorTop("Launch_" + std::to_string(index) + "_text", Ogre::ColourValue(0.8, 0.8, 0.8));
}

void ZappyGui::MainMenu::_createQuit(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, std::size_t index)
{
    _quit.reset(new ZappyGui::Button(overlay, "Quit_" + std::to_string(index), "MenuButtonDefault", closeWindow));
    _quit->panelSetDimensions(500, 150);
    _quit->panelSetPosition(width / 2 - 250, height / 2 + 200);
    _quit->setMaterials("MenuButtonDefault", "MenuButtonHover", "MenuButtonClick");

    _quit->addTextArea("Quit_" + std::to_string(index) + "_text", 250, 55, "defaultFont");
    _quit->textSetAlignment("Quit_" + std::to_string(index) + "_text", Ogre::TextAreaOverlayElement::Center);
    _quit->textSetText("Quit_" + std::to_string(index) + "_text", "Quit");
    _quit->textSetCharacterHeight("Quit_" + std::to_string(index) + "_text", 50);
    _quit->textSetColorBottom("Quit_" + std::to_string(index) + "_text", Ogre::ColourValue(0.7, 0.7, 0.7));
    _quit->textSetColorTop("Quit_" + std::to_string(index) + "_text", Ogre::ColourValue(0.8, 0.8, 0.8));
}
