/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Gui
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include <functional>
    #include <utility>
    #include "Renderer.hpp"
    #include "Camera.hpp"
    #include "Light.hpp"
    #include "Tilemap.hpp"
    #include "SafeQueue.hpp"
    #include "Game.hpp"
    #include "Client.hpp"

namespace ZappyGui {
    class Gui {
        public:
            Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests, float minDelayServerUpdates);
            ~Gui();
            void initialize();
            void run();
            void processCommand(std::string command);
            /// @brief try to convert the given std::vector<std::string> args into an vector of size_t equivalent betwenn startIndex and endIndex
            /// @param args std::vector<std::string> to convert
            /// @param startIndex index to start in the args vector (0 by default)
            /// @param endIndex index to end in the args vector (0 by default for entire args vector)
            /// @return return an vector of size_t with the converted values or an empty one in case of error
            std::vector<std::size_t> convertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex = 0, std::size_t endIndex = static_cast<std::size_t>(-1));
            void setDone(bool done);

            ZappyGui::Renderer &getRenderer() const { return *_renderer.get(); }
            void setMapSize(size_t width, size_t height) { _mapWidth = width; _mapHeight = height; }
            void setTimeUnit(std::size_t timeUnit) { _timeUnit = timeUnit; }
            std::pair<size_t, size_t> getMapSize() const { return std::pair<size_t, size_t>(_mapWidth, _mapHeight); }
            void setTilemap(std::shared_ptr<ZappyGui::Tilemap> tilemap) { _tilemap = tilemap; }
            std::shared_ptr<ZappyGui::Tilemap> getTilemap() { return _tilemap; }
            ZappyGui::Game &getGame() { return _game; }
            std::size_t getTimeUnit() { return _timeUnit; }
            void sendRequest(std::string command, std::vector<std::string> args) { Network::Client::queueRequest(_requests, command, args); }

        private:
            SafeQueue<std::string> &_receive;
            SafeQueue<std::string> &_requests;
            float _minDelayServerUpdates;
            float _waitedServerUpdateDelay;
            std::unique_ptr<ZappyGui::Renderer> _renderer;
            std::shared_ptr<ZappyGui::Tilemap> _tilemap;
            std::vector<Light> _lights;
            ZappyGui::Game _game;
            size_t _mapWidth = 0;
            size_t _mapHeight = 0;
            std::size_t _timeUnit;

            std::unordered_map<std::string, std::function<void (Gui &, std::vector<std::string>)>>_commands;

            std::vector<std::size_t> _ImplconvertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex, std::size_t endIndex);
    };

    void quit(ZappyGui::Gui &gui, std::vector<std::string> args);
    void msz(ZappyGui::Gui &gui, std::vector<std::string> args);
    void bct(ZappyGui::Gui &gui, std::vector<std::string> args);
    void tna(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pnw(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pdi(ZappyGui::Gui &gui, std::vector<std::string> args);
    void ppo(ZappyGui::Gui &gui, std::vector<std::string> args);
    void plv(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pin(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pex(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pbc(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pic(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pie(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pfk(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pdr(ZappyGui::Gui &gui, std::vector<std::string> args);
    void pgt(ZappyGui::Gui &gui, std::vector<std::string> args);
    void enw(ZappyGui::Gui &gui, std::vector<std::string> args);
    void ebo(ZappyGui::Gui &gui, std::vector<std::string> args);
    void edi(ZappyGui::Gui &gui, std::vector<std::string> args);
    void sgt(ZappyGui::Gui &gui, std::vector<std::string> args);
    void sst(ZappyGui::Gui &gui, std::vector<std::string> args);
    void seg(ZappyGui::Gui &gui, std::vector<std::string> args);
    void smg(ZappyGui::Gui &gui, std::vector<std::string> args);
    void suc(ZappyGui::Gui &gui, std::vector<std::string> args);
    void sbp(ZappyGui::Gui &gui, std::vector<std::string> args);
}

#endif
