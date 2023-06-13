/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include <functional>
    #include "Renderer.hpp"
    #include "Camera.hpp"
    #include "Light.hpp"
    #include "Tilemap.hpp"
    #include "SafeQueue.hpp"

namespace ZappyGui {


    class Gui {
        public:
            Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests);
            ~Gui() = default;
            void initialize();
            void run();
            void processCommand(std::string command);
            void setDone(bool done);

        private:
            SafeQueue<std::string> &_receive;
            SafeQueue<std::string> &_requests;
            std::unique_ptr<ZappyGui::Renderer> _renderer;
            size_t _mapWidth = 0;
            size_t _mapHeight = 0;

            std::unordered_map<std::string, std::function<void (Gui &, std::vector<std::string>)>>_commands;
    };

    void quit(ZappyGui::Gui &gui, std::vector<std::string> args);
    void msz(ZappyGui::Gui &gui, std::vector<std::string> args);
}

#endif
