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
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_syswm.h>
    #include "Utils.hpp"
    #include "Camera.hpp"

namespace ZappyGui {

    class Renderer {
        public:
            Renderer(std::string name, int width, int height, std::string resourceFile);
            ~Renderer();

            std::shared_ptr<Ogre::SceneManager> getSceneManager();
            void registerCamera(std::shared_ptr<ZappyGui::Camera> camera);
            void render();
            bool renderOneFrame();
            void event();
            bool isDone();
            void processInputs();
        protected:
        private:
            void _moveCamera(ZappyGui::Real x, ZappyGui::Real y, ZappyGui::Real z);
            void _loadResources(std::string resourceFile);
            void _checkKeydown(SDL_Event &event);
            void _checkKeyup(SDL_Event &event);
            void _initInputs();
            void _processInputsCamMovement();
            void _processInputsCamRotation();

            std::map<SDL_KeyCode, bool> _inputs;
            std::unique_ptr<SDL_Window, ZappyGui::nop> _sdlWindow;
            std::unique_ptr<Ogre::RenderWindow, ZappyGui::nop> _window;
            std::unique_ptr<Ogre::Root> _root;
            std::shared_ptr<Ogre::SceneManager> _sceneManager;
            std::unique_ptr<Ogre::Viewport, ZappyGui::nop> _viewport;
            std::shared_ptr<ZappyGui::Camera> _camera;
            bool _done;
            float _camRotationSpeed;
            float _camMovementSpeed;
    };

}

#endif /* !RENDERER_HPP_ */
