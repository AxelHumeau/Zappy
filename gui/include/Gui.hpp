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
    #include <list>
    #include "Renderer.hpp"
    #include "Camera.hpp"
    #include "Light.hpp"
    #include "Tilemap.hpp"
    #include "SafeQueue.hpp"
    #include "Game.hpp"
    #include "Client.hpp"
    #include "TimerPtr.hpp"
    #include "Particles/BroadcastParticle.hpp"
    #include "Button.hpp"

namespace ZappyGui {

    class Gui {
        public:
            Gui(SafeQueue<std::string> &receive, SafeQueue<std::string> &requests, float minDelayServerUpdates);
            ~Gui() = default;

            /// @brief Loads element of the scene and displays the title screen.
            void initialize();

            /// @brief Main loop of the game.
            void run();

            /// @brief Processes the command received from the server.
            /// @param command String of the command.
            void processCommand(std::string command);

            /// @brief try to convert the given std::vector<std::string> args into an vector of size_t equivalent betwenn startIndex and endIndex
            /// @param args std::vector<std::string> to convert
            /// @param startIndex index to start in the args vector (0 by default)
            /// @param endIndex index to end in the args vector (0 by default for entire args vector)
            /// @return return an vector of size_t with the converted values or an empty one in case of error
            std::vector<std::size_t> convertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex = 0, std::size_t endIndex = static_cast<std::size_t>(-1));

            /// @brief set the state to done and end the run loop
            /// @param done new state
            void setDone(bool done);

            /// @brief Getter to the renderer.
            /// @return Reference to the renderer.
            ZappyGui::Renderer &getRenderer() const { return *_renderer.get(); }

            /// @brief Sets the map size to the one given.
            /// @param width New width of the map.
            /// @param height New height of the map.
            void setMapSize(size_t width, size_t height) { _mapWidth = width; _mapHeight = height; }

            /// @brief Sets the new time unit for the game.
            /// @param timeUnit New time unit.
            void setTimeUnit(std::size_t timeUnit) { _timeUnit = timeUnit; }

            /// @brief Getter for the map size.
            /// @return Pair with the width and height of the map.
            std::pair<size_t, size_t> getMapSize() const { return std::pair<size_t, size_t>(_mapWidth, _mapHeight); }

            /// @brief Sets the tilemap of the game.
            /// @param tilemap Shared pointer to the new tilemap.
            void setTilemap(std::shared_ptr<ZappyGui::Tilemap> tilemap) { _tilemap = tilemap; }

            /// @brief Getter for the tilemap.
            /// @return Shared pointer to the tilemap.
            std::shared_ptr<ZappyGui::Tilemap> getTilemap() { return _tilemap; }

            /// @brief Getter for the game.
            /// @return Reference to the game.
            ZappyGui::Game &getGame() { return _game; }

            /// @brief Getter for the time unit of the game.
            /// @return The current time unit of the game.
            std::size_t getTimeUnit() { return _timeUnit; }

            /// @brief Sends a request to the server.
            /// @param command String of the command to send.
            /// @param args Vector of string with the parameters of the command.
            void sendRequest(std::string command, std::vector<std::string> args) { Network::Client::queueRequest(_requests, command, args); }

            /// @brief add a new broadcast particle effect at a given position
            /// @param position the center of the particle effect
            void addBroadcastParticle(Vector3 position);

            /// @brief Sets the value for the end of the initialization loop
            /// @param value Boolean use to set endInitialization. True to quit the loop, false otherwise.
            void setEndInitialization(bool value) { _endInitialization = value; };

        private:
            /// @brief Checks the mouse clicks given by the renderer.
            void _checkMouseClick();

            /// @brief Updates the contents of the panels on the sceen.
            void _updatePanels();

            /// @brief Creates a text area on the panel passed in parameter with default values
            /// @param p Panel on which to put the text
            /// @param name Name of the text area
            /// @param pos Position of the text area on the panel
            /// @param text Text to display on the text area
            void _createDefaultTextArea(std::shared_ptr<ZappyGui::Panel> p, std::string name, ZappyGui::Vector2i pos, std::string text);

            /// @brief Get a pointer to a tile using its entity name in its game object.
            /// @param name Name of the entity to find.
            /// @return Unique pointer to the tile
            std::unique_ptr<ZappyGui::Tile, Nop> _getTileByName(std::string name);

            /// @brief Creates a panel with informations of the tile.
            /// @param tile Unique pointer to the tile.
            /// @param pos Position of the panel on the screen.
            void _createTilePanel(std::unique_ptr<Tile, Nop> tile, ZappyGui::Vector2 pos);

            /// @brief Get a pointer to a player using its entity name in its game object.
            /// @param name Name of the entity.
            /// @return Unique pointer to the player.
            std::unique_ptr<ZappyGui::Player, ZappyGui::Nop> _getPlayerByName(std::string name);

            /// @brief Creates a panel with informations of the player.
            /// @param player Unique pointer to the player.
            /// @param pos Position on the screen.
            void _createPlayerPanel(std::unique_ptr<Player, Nop> player, ZappyGui::Vector2 pos);

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
            std::list<TimerPtr<BroadcastParticle>> _broadcastParticles;
            std::unique_ptr<Ogre::RaySceneQuery, Nop> _sceneQuery;
            std::shared_ptr<std::map<std::string, std::unique_ptr<ZappyGui::Tile, Nop>>> _tilePanels;
            std::shared_ptr<std::map<std::string, std::size_t>> _playerPanels;
            bool _endInitialization = false;

            std::unordered_map<std::string, std::function<void (Gui &, std::vector<std::string>)>>_commands;

            std::vector<std::size_t> _ImplconvertArgsToSize_t(std::vector<std::string> args, std::size_t startIndex, std::size_t endIndex);
    };

    void updatePlayerPosition(ZappyGui::Player &player, ZappyGui::Gui &gui, std::vector<std::size_t> values);
    void updatePlayerRotation(ZappyGui::Player &player, ZappyGui::Gui &gui, std::vector<std::size_t> values);

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
