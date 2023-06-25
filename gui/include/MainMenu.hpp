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

    class MainMenu {
        public:
            MainMenu(std::shared_ptr<Ogre::Overlay> overlay, int width, int height);
            ~MainMenu() = default;

            void update(ZappyGui::Gui &gui, int x, int y, MouseEvent &event);

        private:
            void _createBackground(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, std::size_t index);

            void _createLaunch(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, int index);

            void _createQuit(std::shared_ptr<Ogre::Overlay> overlay, int width, int height, int index);

            std::unique_ptr<ZappyGui::Panel> _bg;
            std::unique_ptr<ZappyGui::Button> _launch;
            std::unique_ptr<ZappyGui::Button> _quit;
    };

}

#endif /* !MAINMENU_HPP_ */
