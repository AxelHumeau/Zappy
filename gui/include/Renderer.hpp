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

namespace ZappyGui {

    class Renderer {
        public:
            Renderer(std::string name, int width, int height);
            ~Renderer();

            std::shared_ptr<Ogre::SceneManager> getSceneManager();
            void registerCamera(std::shared_ptr<Ogre::Camera> camera);
            void render();
            bool renderOneFrame();
            void event();
            bool isDone();
        protected:
        private:
            std::unique_ptr<SDL_Window, ZappyGui::nop> _sdlWindow;
            std::unique_ptr<Ogre::RenderWindow, ZappyGui::nop> _window;
            std::unique_ptr<Ogre::Root> _root;
            std::shared_ptr<Ogre::SceneManager> _sceneManager;
            std::unique_ptr<Ogre::Viewport, ZappyGui::nop> _viewport;
            bool _done;
    };

}

#endif /* !RENDERER_HPP_ */
