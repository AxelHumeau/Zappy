/*
** EPITECH PROJECT, 2023
** Button.hpp
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_
    #include <functional>
    #include "Panel.hpp"
    #include "Gui.hpp"
    #include "Renderer.hpp"

namespace ZappyGui {

    class Gui;

    /// @brief Button class derived from the Panel class. Used to display and update buttons.
    class Button : public Panel {
        public:
            /// @brief Constructor for the Button class.
            /// @param overlay Shared pointer to the Overlay.
            /// @param buttonName Name of the button.
            /// @param defaultMat Default material for the panel of the button.
            /// @param action Function to use when the button is clicked.
            Button(std::shared_ptr<Ogre::Overlay> overlay, std::string buttonName, std::string defaultMat, std::function<void(ZappyGui::Gui &)> action);
            ~Button() = default;

            /// @brief Updates the button depending of the mouse state.
            /// @param gui Reference to the Gui.
            /// @param x X position of the mouse.
            /// @param y Y position of the mouse.
            /// @param event Current mouse state.
            /// @return Boolean of whether the button has been updated. True if the button has been updated, false otherwise.
            /// Use this when there is multiple buttons to only update the button over the other.
            bool update(Gui &gui, int x, int y, MouseEvent &event);

            /// @brief Sets the materials for every state of the button. If not set, the default materials will be used for all states.
            /// @param defaultMat Name of the default material. Should be loaded in the Assets group in ogre.
            /// @param hoverMat Name of the hover material. Should be loaded in the Assets group in ogre.
            /// @param clickMat Name of the click material. Should be loaded in the Assets group in ogre.
            void setMaterials(std::string defaultMat, std::string hoverMat, std::string clickMat);

        private:
            std::function<void(ZappyGui::Gui &)> _action;
            bool _click = false;

            std::string _defaultMat = "";
            std::string _hoverMat = "";
            std::string _clickMat = "";
    };

}

#endif /* !BUTTON_HPP_ */
