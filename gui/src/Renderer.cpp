/*
** EPITECH PROJECT, 2023
** Renderer.cpp
** File description:
** Renderer
*/

#include "Renderer.hpp"

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

ZappyGui::Renderer::Renderer(std::string name)
{
    _context.reset(new OgreBites::ApplicationContext(name));
    _context->initApp();
    _root.reset(_context->getRoot());
    _sceneManager.reset(_root->createSceneManager(), ZappyGui::nop());
    _shaderGenerator.reset(Ogre::RTShader::ShaderGenerator::getSingletonPtr());
    _shaderGenerator->addSceneManager(_sceneManager.get());
}

ZappyGui::Renderer::~Renderer()
{
    _root.release();
    _sceneManager.reset();
    _shaderGenerator.release();
    _context->closeApp();
}

std::shared_ptr<Ogre::SceneManager> ZappyGui::Renderer::getSceneManager()
{
    return _sceneManager;
}

void ZappyGui::Renderer::registerCamera(std::shared_ptr<Ogre::Camera> camera)
{
    _context->getRenderWindow()->addViewport(camera.get());
}

void ZappyGui::Renderer::render()
{
    KeyHandler keyHandler;
    _context->addInputListener(&keyHandler);
    _root->startRendering();
}
