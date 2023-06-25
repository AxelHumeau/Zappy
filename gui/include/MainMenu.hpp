/*
** EPITECH PROJECT, 2023
** MainMenu.hpp
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
    #define MAINMENU_HPP_
    #include "Gui.hpp"

namespace ZappyGui {

    void endInitialization(ZappyGui::Gui &gui);
    void closeWindow(ZappyGui::Gui &gui);

    /// @brief Creates the main menu for the game.
    class MainMenu {
        public:
            MainMenu(std::shared_ptr<Ogre::Overlay> overlay, int width, int height);
            ~MainMenu() = default;

            /// @brief Updates the buttons on the main menu.
            /// @param gui Reference to the gui.
            /// @param x X position of the mouse.
            /// @param y Y position of the mouse.
            /// @param event Current state of the mouse.
            void update(ZappyGui::Gui &gui, int x, int y, MouseEvent &event);

        private:
            /// @brief Creates the background panel.
            /// @param overlay Shared pointer to the overlay.
            /// @param width Width of the window.
            /// @param height Height of the window.
            /// @param index Main menu id.
            void _createBackground(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, std::size_t index);

            /// @brief Creates the launch button of the main menu.
            /// @param overlay Shared pointer to the overlay.
            /// @param width Width of the window.
            /// @param height Height of the window.
            /// @param index Main menu id.
            void _createLaunch(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, std::size_t index);

            /// @brief Creates the quit button of the main menu.
            /// @param overlay Shared pointer to the overlay.
            /// @param width Width of the window.
            /// @param height Height of the window.
            /// @param index Main menu id.
            void _createQuit(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, std::size_t index);

            std::unique_ptr<ZappyGui::Panel> _bg;
            std::unique_ptr<ZappyGui::Button> _launch;
            std::unique_ptr<ZappyGui::Button> _quit;
    };

}

#endif /* !MAINMENU_HPP_ */
