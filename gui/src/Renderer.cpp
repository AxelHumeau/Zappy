/*
** EPITECH PROJECT, 2023
** Renderer.cpp
** File description:
** Renderer
*/

#include <iostream>
#include <OGRE/OgreColourValue.h>
#include "ResourceLoader.hpp"
#include "Renderer.hpp"

ZappyGui::Renderer::Renderer(std::string name, int width, int height, std::string resourceFile)
{
    _done = false;

    SDL_Init(SDL_INIT_VIDEO);
    _sdlWindow.reset(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0));
    Ogre::NameValuePairList params;
    params["externalWindowHandle"] = "true";

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(_sdlWindow.get(), &wmInfo);

    params["parentWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.x11.window));

    _root.reset(new Ogre::Root("./gui/config/plugins.cfg", "./gui/config/ogre.cfg", "./gui/config/ogre.log"));
    _root->setRenderSystem(_root->getRenderSystemByName("OpenGL Rendering Subsystem"));
    _root->showConfigDialog(NULL);
    _root->restoreConfig();
    _root->initialise(false);

    _window.reset(_root->createRenderWindow(name, width, height, false, &params));
    _window->setVisible(true);

    _loadResources(resourceFile);

    _sceneManager.reset(_root->createSceneManager(), ZappyGui::nop());
}

ZappyGui::Renderer::~Renderer()
{
    _root->destroySceneManager(_sceneManager.get());
    _sceneManager.reset();
    SDL_DestroyWindow(_sdlWindow.get());
    _sdlWindow.release();
}

std::shared_ptr<Ogre::SceneManager> ZappyGui::Renderer::getSceneManager()
{
    return _sceneManager;
}

void ZappyGui::Renderer::registerCamera(std::shared_ptr<Ogre::Camera> camera)
{
    _viewport.reset(_window->addViewport(camera.get()));
    _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
}

void ZappyGui::Renderer::render()
{
    while (true)
    {
        _root->renderOneFrame();
        SDL_GL_SwapWindow(_sdlWindow.get());
    }
}

bool ZappyGui::Renderer::renderOneFrame()
{
    bool ret = _root->renderOneFrame();

    SDL_GL_SwapWindow(_sdlWindow.get());
    return ret;
}

void ZappyGui::Renderer::event()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                // Handle any key presses here.
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Handle mouse clicks here.
                break;
            case SDL_QUIT:
                _done = true;
                break;
            default:
                break;
        }
    }
}

bool ZappyGui::Renderer::isDone()
{
    return _done;
}

void ZappyGui::Renderer::_loadResources(std::string resourceFile)
{
    ZappyGui::ResourceLoader::load(resourceFile);
    ZappyGui::ResourceLoader::initAll();
}
