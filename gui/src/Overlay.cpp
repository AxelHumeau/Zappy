/*
** EPITECH PROJECT, 2023
** Overlay.cpp
** File description:
** Overlay
*/

#include <iostream>
#include "Overlay.hpp"

ZappyGui::Overlay::Overlay(std::string panelName)
{
    _panel.reset(static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", panelName)));
    _panel->setMetricsMode(Ogre::GMM_PIXELS);

    _overlay.reset(Ogre::OverlayManager::getSingletonPtr()->create("Overlay" + panelName));
    _overlay->add2D(_panel.get());
}

ZappyGui::Overlay::~Overlay()
{
}

void ZappyGui::Overlay::showOverlay()
{
    _overlay->show();
}

void ZappyGui::Overlay::hideOverlay()
{
    _overlay->hide();
}

void ZappyGui::Overlay::panelSetPosition(Real left, Real top)
{
    _left = left;
    _top = top;
    _panel->setPosition(left, top);
}

void ZappyGui::Overlay::panelSetDimensions(Real width, Real height)
{
    _width = width;
    _height = height;
    _panel->setDimensions(width, height);
}

void ZappyGui::Overlay::panelSetMaterial(const std::string &matName, const std::string &group)
{
    _panel->setMaterialName(matName, group);
}

void ZappyGui::Overlay::panelSetMetricsMode(Ogre::GuiMetricsMode guiMetricsMode)
{
    _panel->setMetricsMode(guiMetricsMode);
}

void ZappyGui::Overlay::addTextArea(const std::string &name, Real top, Real left, const std::string &fontName)
{
    _textAreas.insert({name, nullptr});
    _textAreas[name].reset(static_cast<Ogre::TextAreaOverlayElement*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", name)));
    textSetMetricsMode(name, Ogre::GMM_PIXELS);
    textSetPosition(name, top, left);
    textSetFont(name, fontName);
    _panel->addChild(_textAreas[name].get());
}

void ZappyGui::Overlay::textSetPosition(const std::string &name, Real top, Real left)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setPosition(top, left);
}

void ZappyGui::Overlay::textSetMetricsMode(const std::string &name, Ogre::GuiMetricsMode guiMetricsMode)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setMetricsMode(guiMetricsMode);
}

void ZappyGui::Overlay::textSetAlignment(const std::string &name, Ogre::TextAreaOverlayElement::Alignment alignment)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setAlignment(alignment);
}

void ZappyGui::Overlay::textSetText(const std::string &name, const std::string &text)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setCaption(text);
}

void ZappyGui::Overlay::textSetCharacterHeight(const std::string &name, Real height)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setCharHeight(height);
}

void ZappyGui::Overlay::textSetFont(const std::string &name, const std::string &fontName)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setFontName(fontName);
}

void ZappyGui::Overlay::textSetColorBottom(const std::string &name, Ogre::ColourValue color)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setColourBottom(color);
}

void ZappyGui::Overlay::textSetColorTop(const std::string &name, Ogre::ColourValue color)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setColourTop(color);
}
