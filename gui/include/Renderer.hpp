/*
** EPITECH PROJECT, 2023
** Renderer.hpp
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
    #define RENDERER_HPP_
    #include <string>
    #include <memory>
    #include <OGRE/Ogre.h>
    #include <OGRE/Bites/OgreApplicationContext.h>
    #include <OGRE/Overlay/OgreOverlayManager.h>
    #include <OGRE/Overlay/OgreOverlayContainer.h>
    #include <OGRE/Overlay/OgreOverlay.h>
    #include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
    #include <OGRE/Overlay/OgreFontManager.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_syswm.h>
    #include <chrono>
    #include <queue>
    #include "Utils.hpp"
    #include "Camera.hpp"
    #include "Panel.hpp"
    #include "VectorMap.hpp"
    #include "Tile.hpp"
    #include "Player.hpp"

namespace ZappyGui {

    struct Mouse {
        bool lbIsPressed;
        int x;
        int y;
    };

    enum MouseEvent {
        NoEvent,
        Click,
        Hold,
        Release,
    };

    /// @brief Encapsulation of ogre rendering system using a sdl2 window, manages it and its inputs
    class Renderer {
        public:
            Renderer(std::string name, int width, int height, std::string resourceFile);
            ~Renderer();

            /// @brief Returns a shared pointer to the scene manager
            /// @return Shared pointer to the scene manager
            std::shared_ptr<Ogre::SceneManager> getSceneManager();

            /// @brief Registers a new camera in the window viewpoint
            /// @param camera Shared pointer to the camera
            void registerCamera(std::shared_ptr<ZappyGui::Camera> camera);

            /// @brief Render a single frame of the scene. First update the ogre scene and then render the sdl2 window
            bool renderOneFrame();

            /// @brief Renders a single frame of the sdl2 window
            void renderSdl2();

            /// @brief Handles the window events and inputs
            void event();

            /// @brief Returns the current state of the window, false if it is running, true if it's over
            /// @return Boolean of the state of the window
            bool isDone();

            /// @brief Sets the current state of the window to the one passed in parameter
            /// @param done Boolean of the new state of the window
            void setDone(bool done);

            /// @brief Processes the inputs of the user
            void processInputs();

            /// @brief Updates the delta time since the last update. Should be called at the beginning of the loop
            void updateDeltaTime();

            /// @brief Getter for the current delta time in second
            /// @return Float of the delta time
            const float &getDeltaTime() const;

            /// @brief Changes the state of the skybox with the one in parameter
            /// @param visible Boolean which sets the visiblity of the SkyBox. True is visible, false is not.
            void setSkyBoxVisibility(bool visible);

            /// @brief Loads a font into ogre.
            /// @param name String of the font name in ogre.
            /// @param group String defining the group in which the font is loaded.
            /// @param fontFile String of the file path to the string. File path to the directory needs to be loaded in ogre before.
            /// @param size String defining the size of the font.
            /// @param resolution String defining the resolution of the font.
            void loadFont(std::string name, std::string group, std::string fontFile, std::string size, std::string resolution);

            /// @brief Getter for the vector map of the panels
            /// @return Reference to the vector map of the panels
            VectorMap<std::string, std::shared_ptr<ZappyGui::Panel>> &getPanels();

            /// @brief Getter for the shared pointer of the overlay
            /// @return Shared pointer of the overlay
            std::shared_ptr<Ogre::Overlay> getOverlay();

            /// @brief Handles the events for the mouse.
            void mouseEvent();

            /// @brief Checks if the size of the mouse clicks queue is null.
            /// @return Boolean, true if it is empty, false otherwise.
            bool mouseClicksEmpty();

            /// @brief Pops the mouse click from the queue
            /// @return Vector2 of the mouse click position relative to the screen. The value is between 0 and 1.
            ZappyGui::Vector2 popMouseClicks();

            /// @brief Getter for the camera.
            /// @return Shared pointer to the camera.
            std::shared_ptr<ZappyGui::Camera> getCamera();

            /// @brief Sets the tile panels. Use to delete the deleted panels outside of the renderer.
            /// @param tilePanels Shared pointer to the tile panels map.
            void setTilePanels(std::shared_ptr<std::map<std::string, std::unique_ptr<ZappyGui::Tile, Nop>>> tilePanels);

            /// @brief Sets the player panels. Use to delete the deleted panels outside of the renderer.
            /// @param playerPanels Shared pointer to the player panels map.
            void setPlayerPanels(std::shared_ptr<std::map<std::string, std::size_t>> playerPanels);

            /// @brief Getter for the window dimentions.
            /// @return Vector2i of the window dimentions.
            ZappyGui::Vector2i getDimensions() { return ZappyGui::Vector2i(_width, _height); };

            /// @brief Getter for the current mouse position.
            /// @return Vector2i of the current mouse position.
            ZappyGui::Vector2i getMousePosition() { return ZappyGui::Vector2i(_curMouse.x, _curMouse.y); };

            /// @brief Getter for the mouse event, which is the state of the left click.
            /// @return MouseEvent of the current mouse state.
            ZappyGui::MouseEvent &getMouseEvent() { return _mouseEvent; };

        private:
            /// @brief Loads all resources in the file in parameter in ogre
            /// @param resourceFile File containing the resources to load
            void _loadResources(std::string resourceFile);

            /// @brief Updates the state of the key that are pressed
            /// @param event Reference to the current event
            void _checkKeydown(SDL_Event &event);

            /// @brief Updates the state of the key that are unpressed
            /// @param event Reference to the current event
            void _checkKeyup(SDL_Event &event);

            /// @brief Initialize the input list
            void _initInputs();

            /// @brief Handles the camera movement based on the inputs
            void _processInputsCamMovement();

            /// @brief Handles the camera rotation based on the inputs
            void _processInputsCamRotation();

            /// @brief Handles the mouse event when the left button is clicked.
            void _mouseEventOnClick();

            /// @brief Handles the mouse event when the left button is holded.
            void _mouseEventHold();

            /// @brief Handles the mouse event when the left button is released.
            void _mouseEventOnRelease();

            /// @brief Handles the mouse event when the left button is neither clicked, holded nor released.
            void _mouseEventUpdate();

            std::map<SDL_KeyCode, bool> _inputs;
            std::unique_ptr<SDL_Window, ZappyGui::Nop> _sdlWindow;
            std::unique_ptr<Ogre::RenderWindow, ZappyGui::Nop> _window;
            std::unique_ptr<Ogre::Root> _root;
            std::unique_ptr<Ogre::OverlaySystem, ZappyGui::Nop> _overlaySystem;
            std::unique_ptr<Ogre::Viewport, ZappyGui::Nop> _viewport;
            std::shared_ptr<ZappyGui::Camera> _camera;
            std::shared_ptr<Ogre::SceneManager> _sceneManager;
            std::unique_ptr<Ogre::RTShader::ShaderGenerator, ZappyGui::Nop> _shaderGenerator;
            std::unique_ptr<OgreBites::SGTechniqueResolverListener, ZappyGui::Nop> _resolverListener;
            std::shared_ptr<Ogre::Overlay> _overlay;
            bool _done;
            float _camRotationSpeed;
            float _camMovementSpeed;
            int _width;
            int _height;
            float _deltaTime;
            std::chrono::steady_clock::time_point _lastTime;
            ZappyGui::Mouse _curMouse;
            ZappyGui::Mouse _prevMouse;
            std::string _dragPanelName;
            int _mDragPosX;
            int _mDragPosY;
            std::queue<ZappyGui::Vector2> _mouseClicks;
            VectorMap<std::string, std::shared_ptr<ZappyGui::Panel>> _panels;
            std::shared_ptr<std::map<std::string, std::unique_ptr<ZappyGui::Tile, ZappyGui::Nop>>> _tilePanels;
            std::shared_ptr<std::map<std::string, std::size_t>> _playerPanels;
            MouseEvent _mouseEvent = MouseEvent::NoEvent;
    };

}

#endif /* !RENDERER_HPP_ */
