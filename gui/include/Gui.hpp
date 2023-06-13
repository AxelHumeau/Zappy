/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include "Renderer.hpp"
    #include "Camera.hpp"
    #include "Light.hpp"
    #include "Tilemap.hpp"
    #include "SafeQueue.hpp"

namespace ZappyGui {

    namespace GuiCommands {
        void quit(std::vector<std::string>);
        void msz(std::vector<std::string>);

        static const std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> commands = {
            {"quit", quit},
            {"msz", msz}
        };
    }

    class Gui {
        public:
            Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests);
            ~Gui() = default;
            void initialize();
            void run();

        private:
            SafeQueue<std::string> &_receive;
            SafeQueue<std::string> &_requests;
            std::unique_ptr<ZappyGui::Renderer> _renderer;
            size_t _mapWidth = 0;
            size_t _mapHeight = 0;

    };
}

#endif
