/*
** EPITECH PROJECT, 2023
** Renderer.cpp
** File description:
** Renderer
*/

#include "Renderer.hpp"

ZappyGui::Renderer::Renderer(std::string name)
{
    _context.reset(new OgreBites::ApplicationContext(name));
    _context->initApp();
    _root.reset(_context->getRoot());
    _sceneManager.reset(_root->createSceneManager(), ZappyGui::nop());
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./gui/assets/hamster.zip", "Zip", "Assets");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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
    _root->startRendering();
}

bool ZappyGui::Renderer::renderOneFrame()
{
    return _root->renderOneFrame();
}

void ZappyGui::Renderer::setKeyHandler()
{
    _keyHandler.reset(new KeyHandler());
    _context->addInputListener(_keyHandler.get());
}
