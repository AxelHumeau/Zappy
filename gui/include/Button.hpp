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

    class Button : public Panel {
        public:
            Button(std::shared_ptr<Ogre::Overlay> overlay, std::string buttonName, std::string defaultMat, std::function<void(ZappyGui::Gui &)> action);
            ~Button() = default;

            bool update(Gui &gui, int x, int y, MouseEvent &event);

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
