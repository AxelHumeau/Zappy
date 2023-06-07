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
    _sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
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

void ZappyGui::Renderer::registerCamera(std::shared_ptr<ZappyGui::Camera> camera)
{
    _viewport.reset(_window->addViewport(camera->getCamera().get()));
    _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    _camera = camera;
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
                _checkKeydown(event);
                break;
            case SDL_KEYUP:
                _checkKeyup(event);
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

void ZappyGui::Renderer::_checkKeydown(SDL_Event &event)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_z:
            _inputs[SDLK_z] = true;
            break;
        case SDLK_s:
            _inputs[SDLK_s] = true;
            break;
        case SDLK_q:
            _inputs[SDLK_q] = true;
            break;
        case SDLK_d:
            _inputs[SDLK_d] = true;
            break;
        case SDLK_SPACE:
            _inputs[SDLK_SPACE] = true;
            break;
        case SDLK_LCTRL:
            _inputs[SDLK_LCTRL] = true;
            break;
        default:
            break;
    }
}

void ZappyGui::Renderer::_checkKeyup(SDL_Event &event)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_z:
            _inputs[SDLK_z] = false;
            break;
        case SDLK_s:
            _inputs[SDLK_s] = false;
            break;
        case SDLK_q:
            _inputs[SDLK_q] = false;
            break;
        case SDLK_d:
            _inputs[SDLK_d] = false;
            break;
        case SDLK_SPACE:
            _inputs[SDLK_SPACE] = false;
            break;
        case SDLK_LCTRL:
            _inputs[SDLK_LCTRL] = false;
            break;
        default:
            break;
    }
}

void ZappyGui::Renderer::processInputs()
{
    if (_inputs[SDLK_z] && !_inputs[SDLK_s])
        _moveCamera(0.0, 0.0, -0.15);
    if (_inputs[SDLK_s] && !_inputs[SDLK_z])
        _moveCamera(0.0, 0.0, 0.15);

    if (_inputs[SDLK_q] && !_inputs[SDLK_d])
        _moveCamera(-0.15, 0.0, 0.0);
    if (_inputs[SDLK_d] && !_inputs[SDLK_q])
        _moveCamera(0.15, 0.0, 0.0);

    if (_inputs[SDLK_SPACE] && !_inputs[SDLK_LCTRL])
        _moveCamera(0.0, 0.15, 0.0);
    if (_inputs[SDLK_LCTRL] && !_inputs[SDLK_SPACE])
        _moveCamera(0.0, -0.15, 0.0);
}

void ZappyGui::Renderer::_initInputs()
{
    _inputs[SDLK_z] = false;
    _inputs[SDLK_s] = false;
    _inputs[SDLK_q] = false;
    _inputs[SDLK_d] = false;
    _inputs[SDLK_SPACE] = false;
    _inputs[SDLK_LCTRL] = false;
}

void ZappyGui::Renderer::_moveCamera(ZappyGui::Real x, ZappyGui::Real y, ZappyGui::Real z)
{
    if (_camera == nullptr)
        return;

    ZappyGui::Vector3 pos = _camera->getPosition();

    pos.x += x;
    pos.y += y;
    pos.z += z;
    _camera->setPosition(pos.x, pos.y, pos.z);
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
