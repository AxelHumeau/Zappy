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

    /// @brief Class representing a 2d rectangle
    class Rect {
        public:
            /// @brief Returns if the point is in the rectangle
            /// @param x X point position
            /// @param y Y point position
            /// @return Boolean, true if the point is in the rectangle, false otherwise
            bool isInRect(int x, int y)
            {
                if (x > left && x < left + width && y > top && y < top + height)
                    return true;
                return false;
            };

            Real left;
            Real top;
            Real width;
            Real height;
    };

    /// @brief Class encapsulating an Ogre::OverlayElement used as a close button for the overlay
    class ClosePanel {
        public:
            ClosePanel(std::string name, Rect r, std::string defaultMat, std::string hoverMat, std::string clickMat);

            ~ClosePanel();

            /// @brief Updates the material of the button
            void update();

            /// @brief Returns the shared pointer of the panel
            /// @return Shared pointer to the panel
            std::shared_ptr<Ogre::OverlayElement> getPointer();

            Rect rect;

            bool isHover;
            bool isClick;
        private:
            std::shared_ptr<Ogre::OverlayElement> _panel;
            std::string _defaultMat;
            std::string _hoverMat;
            std::string _clickMat;
    };

    class Panel {
        public:
            Panel(std::shared_ptr<Ogre::Overlay> overlay, std::string panelName, bool dragabble = true);
            ~Panel();

            /// @brief Sets the position of the panel
            /// @param left Position of the left side of the panel (X position)
            /// @param top Position of the top side of the panel (Y position)
            void panelSetPosition(Real left, Real top);

            /// @brief Sets the dimenstions of the panel
            /// @param width Width of the panel
            /// @param height Height of the panel
            void panelSetDimensions(Real width, Real height);

            /// @brief Sets the material of the panel
            /// @param matName std::string of the material name. Material needs to be loaded in ogre before
            /// @param group std::string of the group in which the material is. General by default.
            void panelSetMaterial(const std::string &matName, const std::string &group = Ogre::OverlayElement::DEFAULT_RESOURCE_GROUP);

            /// @brief Sets metrics mode for the panel. Change in the constructor to be in pixel.
            /// @param guiMetricsMode Metrics mode to use
            void panelSetMetricsMode(Ogre::GuiMetricsMode guiMetricsMode);


            /// @brief Adds a new text area on the panel.
            /// @param name std::string of the text area name. Name should be unique (use by convention PanelName_TextAreaName).
            /// @param left Position of the left side of the text area relative to the panel (X position)
            /// @param top Position of the top side of the text area relative to the panel (Y position)
            /// @param fontName std::string of the name of the font to use. Fonts needs to be in the Assets group.
            void addTextArea(const std::string &name, Real left, Real top, const std::string &fontName);

            /// @brief Sets the position of the text area relative to the panel.
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param left Position of the left side of the text area relative to the panel (X position)
            /// @param top Position of the top side of the text area relative to the panel (Y position)
            void textSetPosition(const std::string &name, Real left, Real top);

            /// @brief Sets the metrics mode of the text area.
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param guiMetricsMode Metrics mode to use
            void textSetMetricsMode(const std::string &name, Ogre::GuiMetricsMode guiMetricsMode);

            /// @brief Sets the alignement of the text area relative to the panel.
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param alignment Alignement mode.
            void textSetAlignment(const std::string &name, Ogre::TextAreaOverlayElement::Alignment alignment);

            /// @brief Sets the text in the text area.
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param text std::string of the text.
            void textSetText(const std::string &name, const std::string &text);

            /// @brief Sets the height of the characters in the text area.
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param height Height to use.
            void textSetCharacterHeight(const std::string &name, Real height);

            /// @brief Sets the font to use in the text area
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param fontName std::string of the name of the font to use. Fonts needs to be in the Assets group.
            void textSetFont(const std::string &name, const std::string &fontName);

            /// @brief Sets the color of the bottom of the letter.
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param color Ogre::ColourValue to use.
            void textSetColorBottom(const std::string &name, Ogre::ColourValue color);

            /// @brief Sets the color of the top of the letter.
            /// @param name Name of the text area to change position. If it doesn't exist in this panel, does nothing.
            /// @param color Ogre::ColourValue to use.
            void textSetColorTop(const std::string &name, Ogre::ColourValue color);

            /// @brief Adds a close button on the panel.
            /// @param r Rect of the close button relative to the panel.
            /// @param defaultMat std::string of the default material of the button. Needs to be in Assets.
            /// @param hoverMat std::string of the hover material of the button. Used when the mouse goes over the button. Needs to be in Assets.
            /// @param clickMat std::string of the click material of the button. Used when the button is clicked. Needs to be in Assets.
            void addCloseButton(Rect r, std::string defaultMat, std::string hoverMat, std::string clickMat);

            /// @brief Returns the panel name
            /// @return std::string of the panel name
            std::string getName();

            /// @brief Returns the rectangle of the panel
            /// @return Rect of the panel
            ZappyGui::Rect getRect();

            bool isDraggable;
            std::unique_ptr<ZappyGui::ClosePanel> closeButton;

        protected:
            std::shared_ptr<Ogre::Overlay> _overlay;
            std::unique_ptr<Ogre::OverlayContainer, Nop> _panel;
            std::map<std::string, std::unique_ptr<Ogre::TextAreaOverlayElement, Nop>> _textAreas;

            std::string _panelName;
            Rect _rect;
    };

}

#endif /* !OVERLAY_HPP_ */
