/*
** EPITECH PROJECT, 2023
** Button.cpp
** File description:
** Button
*/

#include "Button.hpp"

ZappyGui::Button::Button(std::shared_ptr<Ogre::Overlay> overlay, std::string buttonName, std::string defaultMat, std::function<void(ZappyGui::Gui &)> action):
Panel(overlay, buttonName, false)
{
    _action = action;
    _defaultMat = defaultMat;
    panelSetMaterial(_defaultMat, "Assets");
}

bool ZappyGui::Button::update(Gui &gui, int x, int y, MouseEvent &event)
{
    if (!_rect.isInRect(x, y))
    {
        if (event == MouseEvent::Release || event == MouseEvent::NoEvent)
            panelSetMaterial(_defaultMat, "Assets");
        return false;
    }
    switch (event)
    {
    case MouseEvent::NoEvent:
        if (_hoverMat != "")
            panelSetMaterial(_hoverMat, "Assets");
        break;
    case MouseEvent::Click:
        if (_clickMat != "")
            panelSetMaterial(_clickMat, "Assets");
        _click = true;
    case MouseEvent::Hold:
        break;
    case MouseEvent::Release:
        if (!_click)
            break;
        if (_defaultMat != "")
            panelSetMaterial(_defaultMat, "Assets");
        _action(gui);
        _click = false;
        break;
    default:
        break;
    }
    return true;
}

void ZappyGui::Button::setMaterials(std::string defaultMat, std::string hoverMat, std::string clickMat)
{
    if (defaultMat != "")
        _defaultMat = defaultMat;
    if (hoverMat != "")
        _hoverMat = hoverMat;
    if (clickMat != "")
        _clickMat = clickMat;
};
