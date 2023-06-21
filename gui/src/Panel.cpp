/*
** EPITECH PROJECT, 2023
** Panel.cpp
** File description:
** Panel
*/

#include <iostream>
#include "Panel.hpp"

ZappyGui::ClosePanel::ClosePanel(std::string name, Rect r, std::string defaultMat, std::string hoverMat, std::string clickMat):
rect(r), isHover(false), isClick(false), _defaultMat(defaultMat), _hoverMat(hoverMat), _clickMat(clickMat)
{
    _panel.reset(static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", name)), ZappyGui::Nop{});
    _panel->setMetricsMode(Ogre::GMM_PIXELS);

    _panel->setPosition(rect.left, rect.top);
    _panel->setDimensions(rect.width, rect.height);

    _panel->setMaterialName(_defaultMat, "Assets");
}

ZappyGui::ClosePanel::~ClosePanel()
{
    Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(_panel.get());
}

void ZappyGui::ClosePanel::update()
{
    if (isHover)
        _panel->setMaterialName(_hoverMat, "Assets");
    else if (isClick)
        _panel->setMaterialName(_clickMat, "Assets");
    else
        _panel->setMaterialName(_defaultMat, "Assets");
}

std::shared_ptr<Ogre::OverlayElement> ZappyGui::ClosePanel::getPointer()
{
    return _panel;
}

ZappyGui::Panel::Panel(std::shared_ptr<Ogre::Overlay> overlay, std::string panelName, bool draggable)
{
    _panel.reset(static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", panelName)));
    _panel->setMetricsMode(Ogre::GMM_PIXELS);

    isDraggable = draggable;

    _overlay = overlay;
    _overlay->add2D(_panel.get());

    _panelName = panelName;

    closeButton.reset(nullptr);
}

ZappyGui::Panel::~Panel()
{
    _overlay->remove2D(_panel.get());
    Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(_panel.get());
    for (auto &ta : _textAreas)
        Ogre::OverlayManager::getSingletonPtr()->destroyOverlayElement(ta.second.get());
}

void ZappyGui::Panel::panelSetPosition(Real left, Real top)
{
    _rect.left = left;
    _rect.top = top;
    _panel->setPosition(left, top);
}

void ZappyGui::Panel::panelSetDimensions(Real width, Real height)
{
    _rect.width = width;
    _rect.height = height;
    _panel->setDimensions(width, height);
}

void ZappyGui::Panel::panelSetMaterial(const std::string &matName, const std::string &group)
{
    _panel->setMaterialName(matName, group);
}

void ZappyGui::Panel::panelSetMetricsMode(Ogre::GuiMetricsMode guiMetricsMode)
{
    _panel->setMetricsMode(guiMetricsMode);
}

void ZappyGui::Panel::addTextArea(const std::string &name, Real top, Real left, const std::string &fontName)
{
    _textAreas.insert({name, nullptr});
    _textAreas[name].reset(static_cast<Ogre::TextAreaOverlayElement*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", name)));
    textSetMetricsMode(name, Ogre::GMM_PIXELS);
    textSetPosition(name, top, left);
    textSetFont(name, fontName);
    _panel->addChild(_textAreas[name].get());
}

void ZappyGui::Panel::textSetPosition(const std::string &name, Real top, Real left)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setPosition(top, left);
}

void ZappyGui::Panel::textSetMetricsMode(const std::string &name, Ogre::GuiMetricsMode guiMetricsMode)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setMetricsMode(guiMetricsMode);
}

void ZappyGui::Panel::textSetAlignment(const std::string &name, Ogre::TextAreaOverlayElement::Alignment alignment)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setAlignment(alignment);
}

void ZappyGui::Panel::textSetText(const std::string &name, const std::string &text)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setCaption(text);
}

void ZappyGui::Panel::textSetCharacterHeight(const std::string &name, Real height)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setCharHeight(height);
}

void ZappyGui::Panel::textSetFont(const std::string &name, const std::string &fontName)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setFontName(fontName);
}

void ZappyGui::Panel::textSetColorBottom(const std::string &name, Ogre::ColourValue color)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setColourBottom(color);
}

void ZappyGui::Panel::textSetColorTop(const std::string &name, Ogre::ColourValue color)
{
    if (_textAreas.find(name) == _textAreas.end())
        return;
    _textAreas[name]->setColourTop(color);
}

ZappyGui::Rect ZappyGui::Panel::getRect()
{
    return _rect;
}

void ZappyGui::Panel::addCloseButton(Rect r, std::string defaultMat, std::string hoverMat, std::string clickMat)
{
    if (closeButton != nullptr)
        return;
    closeButton.reset(new ZappyGui::ClosePanel(_panelName + "_closeButton", r, defaultMat, hoverMat, clickMat));
    _panel->addChild(closeButton->getPointer().get());
}

std::string ZappyGui::Panel::getName()
{
    return _panelName;
}
