/*
** EPITECH PROJECT, 2023
** Overlay.hpp
** File description:
** Overlay
*/

#ifndef OVERLAY_HPP_
    #define OVERLAY_HPP_
    #include <map>
    #include <memory>
    #include <OGRE/Overlay/OgreOverlayManager.h>
    #include <OGRE/Overlay/OgreOverlayContainer.h>
    #include <OGRE/Overlay/OgreOverlay.h>
    #include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
    #include "Utils.hpp"

namespace ZappyGui {

    class Overlay {
        public:
            Overlay(std::string panelName);
            ~Overlay();

            void showOverlay();
            void hideOverlay();

            void panelSetPosition(Real left, Real top);
            void panelSetDimensions(Real width, Real height);
            void panelSetMaterial(const std::string &matName, const std::string &group = Ogre::OverlayElement::DEFAULT_RESOURCE_GROUP);
            void panelSetMetricsMode(Ogre::GuiMetricsMode guiMetricsMode);

            void addTextArea(const std::string &name, Real left, Real top, const std::string &fontName);
            void textSetPosition(const std::string &name, Real left, Real top);
            void textSetMetricsMode(const std::string &name, Ogre::GuiMetricsMode guiMetricsMode);
            void textSetAlignment(const std::string &name, Ogre::TextAreaOverlayElement::Alignment alignment);
            void textSetText(const std::string &name, const std::string &text);
            void textSetCharacterHeight(const std::string &name, Real height);
            void textSetFont(const std::string &name, const std::string &fontName);
            void textSetColorBottom(const std::string &name, Ogre::ColourValue color);
            void textSetColorTop(const std::string &name, Ogre::ColourValue color);

        protected:
            std::unique_ptr<Ogre::Overlay, Nop> _overlay;
            std::unique_ptr<Ogre::OverlayContainer, Nop> _panel;
            std::map<std::string, std::unique_ptr<Ogre::TextAreaOverlayElement, Nop>> _textAreas;

            Real _left;
            Real _top;
            Real _width;
            Real _height;
    };

}

#endif /* !OVERLAY_HPP_ */
