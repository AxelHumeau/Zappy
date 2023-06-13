/*
** EPITECH PROJECT, 2023
** Renderer.cpp
** File description:
** Renderer
*/

#include <iostream>
#include <algorithm>
#include <OGRE/OgreColourValue.h>
#include "ResourceLoader.hpp"
#include "Renderer.hpp"

ZappyGui::Renderer::Renderer(std::string name, int width, int height, std::string resourceFile):
_camRotationSpeed(1.5708), _camMovementSpeed(15), _width(width), _height(height)
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


    _sceneManager.reset(_root->createSceneManager(), ZappyGui::Nop());
    _sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    if (Ogre::RTShader::ShaderGenerator::initialize())
    {
        _shaderGenerator.reset(Ogre::RTShader::ShaderGenerator::getSingletonPtr());
        _shaderGenerator->addSceneManager(_sceneManager.get());

        _resolverListener.reset(new OgreBites::SGTechniqueResolverListener(_shaderGenerator.get()));
        Ogre::MaterialManager::getSingleton().addListener(_resolverListener.get());
    }
    _loadResources(resourceFile);
    _sceneManager->setSkyBox(true, "MaterialHamsterSky");

    _lastTime = std::chrono::steady_clock::now();
    _deltaTime = 0.0;
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
    _camera->getCamera()->setAspectRatio( static_cast<float>(_width) / static_cast<float>(_height) );
}

bool ZappyGui::Renderer::renderOneFrame()
{
    bool ret = _root->renderOneFrame();

    renderSdl2();
    return ret;
}

void ZappyGui::Renderer::renderSdl2()
{
    SDL_GL_SwapWindow(_sdlWindow.get());
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
        case SDLK_UP:
            _inputs[SDLK_UP] = true;
            break;
        case SDLK_DOWN:
            _inputs[SDLK_DOWN] = true;
            break;
        case SDLK_LEFT:
            _inputs[SDLK_LEFT] = true;
            break;
        case SDLK_RIGHT:
            _inputs[SDLK_RIGHT] = true;
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
        case SDLK_UP:
            _inputs[SDLK_UP] = false;
            break;
        case SDLK_DOWN:
            _inputs[SDLK_DOWN] = false;
            break;
        case SDLK_LEFT:
            _inputs[SDLK_LEFT] = false;
            break;
        case SDLK_RIGHT:
            _inputs[SDLK_RIGHT] = false;
            break;
        default:
            break;
    }
}

void ZappyGui::Renderer::processInputs()
{
    _processInputsCamMovement();
    _processInputsCamRotation();
}

void ZappyGui::Renderer::_processInputsCamMovement()
{
    ZappyGui::Vector3 move(0.0, 0.0, 0.0);

    if (_inputs[SDLK_z])
        move.z -= 1.0;
    if (_inputs[SDLK_s] && !_inputs[SDLK_z])
        move.z += 1.0;

    if (_inputs[SDLK_q] && !_inputs[SDLK_d])
        move.x -= 1.0;
    if (_inputs[SDLK_d] && !_inputs[SDLK_q])
        move.x += 1.0;

    if (_inputs[SDLK_SPACE] && !_inputs[SDLK_LCTRL])
        move.y += 1.0;
    if (_inputs[SDLK_LCTRL] && !_inputs[SDLK_SPACE])
        move.y -= 1.0;

    move.normalise();
    move *= _camMovementSpeed * _deltaTime;
    _camera->translate(move, Ogre::Node::TS_LOCAL);
}

void ZappyGui::Renderer::_processInputsCamRotation()
{
    ZappyGui::Vector3 rotation(0.0, 0.0, 0.0);

    if (_inputs[SDLK_UP])
        rotation.y += 1.0;
    if (_inputs[SDLK_DOWN] && !_inputs[SDLK_UP])
        rotation.y -= 1.0;

    if (_inputs[SDLK_LEFT] && !_inputs[SDLK_RIGHT])
        rotation.z += 1.0;
    if (_inputs[SDLK_RIGHT] && !_inputs[SDLK_LEFT])
        rotation.z -= 1.0;
    rotation.normalise();
    rotation *= _camRotationSpeed * _deltaTime;
    _camera->setRotationWorldYaw(Ogre::Radian(0.0), Ogre::Radian(rotation.y), Ogre::Radian(rotation.z));
}

void ZappyGui::Renderer::_initInputs()
{
    _inputs[SDLK_z] = false;
    _inputs[SDLK_s] = false;
    _inputs[SDLK_q] = false;
    _inputs[SDLK_d] = false;
    _inputs[SDLK_SPACE] = false;
    _inputs[SDLK_LCTRL] = false;
    _inputs[SDLK_UP] = false;
    _inputs[SDLK_DOWN] = false;
    _inputs[SDLK_LEFT] = false;
    _inputs[SDLK_RIGHT] = false;
}

bool ZappyGui::Renderer::isDone()
{
    return _done;
}

void ZappyGui::Renderer::setDone(bool done)
{
    _done = done;
}

void ZappyGui::Renderer::_loadResources(std::string resourceFile)
{
    ZappyGui::ResourceLoader::load(resourceFile);
    ZappyGui::ResourceLoader::initAll();
}

void ZappyGui::Renderer::updateDeltaTime()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<float> tmp = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTime);

    _deltaTime = tmp.count();
    _lastTime = now;
}

const float &ZappyGui::Renderer::getDeltaTime() const
{
    return _deltaTime;
}
