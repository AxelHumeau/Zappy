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
    #include <OGRE/Overlay/imgui.h>
    #include <OGRE/Overlay/OgreOverlayManager.h>
    #include <OGRE/Overlay/OgreOverlayContainer.h>
    #include <OGRE/Overlay/OgreOverlay.h>
    #include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
    #include <OGRE/Overlay/OgreFontManager.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_syswm.h>
    #include <chrono>
    #include "Utils.hpp"
    #include "Camera.hpp"

namespace ZappyGui {

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

            void createTestOverlay()
            {
                Ogre::FontPtr mFont = Ogre::FontManager::getSingleton().create("tutorialFont","General");
                mFont->setType(Ogre::FT_TRUETYPE);
                mFont->setSource("Roboto-Bold.ttf");
                mFont->setParameter("size","26");
                mFont->setParameter("resolution","96");
                mFont->load();

                Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "myPanel"));
                panel->setMetricsMode(Ogre::GMM_PIXELS);
                panel->setPosition(0, 0);
                panel->setDimensions(300.0, 100.0);
                panel->setMaterialName("RedTransparent");

                Ogre::TextAreaOverlayElement *textArea = static_cast<Ogre::TextAreaOverlayElement*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", "TextAreaName"));
                textArea->setMetricsMode(Ogre::GMM_PIXELS);
                textArea->setPosition(150, 25);
                textArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
                panel->setDimensions(300, 100);
                textArea->setCaption("Hello, World!");
                textArea->setCharHeight(50);
                textArea->setFontName("tutorialFont");
                textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
                textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

                Ogre::Overlay *overlay = Ogre::OverlayManager::getSingletonPtr()->create("myOverlay");
                overlay->add2D(panel);

                panel->addChild(textArea);

                overlay->show();
            };

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

            std::map<SDL_KeyCode, bool> _inputs;
            std::unique_ptr<SDL_Window, ZappyGui::Nop> _sdlWindow;
            std::unique_ptr<Ogre::RenderWindow, ZappyGui::Nop> _window;
            std::unique_ptr<Ogre::Root> _root;
            std::unique_ptr<Ogre::OverlaySystem, ZappyGui::Nop> _overlaySystem;
            std::shared_ptr<Ogre::SceneManager> _sceneManager;
            std::unique_ptr<Ogre::Viewport, ZappyGui::Nop> _viewport;
            std::shared_ptr<ZappyGui::Camera> _camera;
            std::unique_ptr<Ogre::RTShader::ShaderGenerator, ZappyGui::Nop> _shaderGenerator;
            std::unique_ptr<OgreBites::SGTechniqueResolverListener, ZappyGui::Nop> _resolverListener;
            bool _done;
            float _camRotationSpeed;
            float _camMovementSpeed;
            int _width;
            int _height;
            float _deltaTime;
            std::chrono::steady_clock::time_point _lastTime;
    };

}

#endif /* !RENDERER_HPP_ */
