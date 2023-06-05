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
    #include "Utils.hpp"

namespace ZappyGui {

    class KeyHandler : public OgreBites::InputListener
    {
        bool keyPressed(const OgreBites::KeyboardEvent& evt) override
        {
            if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
            {
                Ogre::Root::getSingleton().queueEndRendering();
            }
            return true;
        }
    };

    class Renderer {
        public:
            Renderer(std::string name);
            ~Renderer();

            std::shared_ptr<Ogre::SceneManager> getSceneManager();
            void registerCamera(std::shared_ptr<Ogre::Camera> camera);
            void render();
            bool renderOneFrame();
            void setKeyHandler();

        protected:
        private:
            std::unique_ptr<OgreBites::ApplicationContext> _context;
            std::unique_ptr<Ogre::Root> _root;
            std::shared_ptr<Ogre::SceneManager> _sceneManager;
            std::unique_ptr<Ogre::RTShader::ShaderGenerator, ZappyGui::nop> _shaderGenerator;
            std::unique_ptr<KeyHandler> _keyHandler;
    };

}

#endif /* !RENDERER_HPP_ */
