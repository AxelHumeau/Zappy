/*
** EPITECH PROJECT, 2023
** Renderer.cpp
** File description:
** Renderer
*/

#include <iostream>
#include <algorithm>
#include <OGRE/OgreColourValue.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>
#include "ResourceLoader.hpp"
#include "Renderer.hpp"

ZappyGui::Renderer::Renderer(std::string name, int width, int height, std::string resourceFile):
_camRotationSpeed(1.5708), _camMovementSpeed(15), _width(width), _height(height)
{
    _done = false;
    _dragPanelName = "";

    _curMouse = { false, 0, 0 };
    _prevMouse = { false, 0, 0 };

    SDL_Init(SDL_INIT_VIDEO);
    _sdlWindow.reset(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN));
    Ogre::NameValuePairList params;
    params["externalWindowHandle"] = "true";

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(_sdlWindow.get(), &wmInfo);

    params["parentWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.x11.window));

    _root.reset(new Ogre::Root("./gui/config/plugins.cfg", "./gui/config/ogre.cfg", "./gui/config/ogre.log"));
    _overlaySystem.reset(new Ogre::OverlaySystem());
    _root->setRenderSystem(_root->getRenderSystemByName("OpenGL Rendering Subsystem"));
    _root->showConfigDialog(NULL);
    _root->restoreConfig();
    _root->initialise(false);

    _window.reset(_root->createRenderWindow(name, width, height, false, &params));
    _window->setVisible(true);

    _sceneManager.reset(_root->createSceneManager(), ZappyGui::Nop());
    _sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    _sceneManager->addRenderQueueListener(_overlaySystem.get());

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

    loadFont("defaultFont", "Assets", "Roboto-Bold.ttf", "26", "156");

    _overlay = std::shared_ptr<Ogre::Overlay>(Ogre::OverlayManager::getSingletonPtr()->create("myOverlay"), ZappyGui::Nop{});
    _overlay->show();
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

    _prevMouse = _curMouse;
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
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetGlobalMouseState(&_curMouse.x,&_curMouse.y);
                    _prevMouse.x = _curMouse.x;
                    _prevMouse.y = _curMouse.y;
                    _curMouse.lbIsPressed = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    _curMouse.lbIsPressed = false;
                }
                break;
            case SDL_QUIT:
                _done = true;
                break;
            case SDL_MOUSEMOTION:
                _prevMouse.x = _curMouse.x;
                _prevMouse.y = _curMouse.y;
                SDL_GetGlobalMouseState(&_curMouse.x,&_curMouse.y);
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
    mouseEvent();
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

void ZappyGui::Renderer::setSkyBoxVisibility(bool visible)
{
    _sceneManager->setSkyBox(visible, "MaterialHamsterSky");
}

void ZappyGui::Renderer::loadFont(std::string name, std::string group, std::string fontFile, std::string size, std::string resolution)
{
    Ogre::FontPtr mFont = Ogre::FontManager::getSingleton().create(name, group);
    mFont->setType(Ogre::FT_TRUETYPE);
    mFont->setSource(fontFile);
    mFont->setParameter("size", size);
    mFont->setParameter("resolution", resolution);
    mFont->load();
}

VectorMap<std::string, std::shared_ptr<ZappyGui::Panel>> &ZappyGui::Renderer::getPanels()
{
    return _panels;
}

std::shared_ptr<Ogre::Overlay> ZappyGui::Renderer::getOverlay()
{
    return _overlay;
}

void ZappyGui::Renderer::_mouseEventOnClick()
{
    if (!_prevMouse.lbIsPressed && _curMouse.lbIsPressed)
    {
        for (std::size_t i = 0; i < _panels.size(); i++)
        {
            if (_panels.at(i).second->getRect().isInRect(_curMouse.x, _curMouse.y) && _panels.at(i).second->isDraggable)
            {
                if (_panels.at(i).second->closeButton != nullptr &&
                    _panels.at(i).second->closeButton->rect.isInRect(_curMouse.x - _panels.at(i).second->getRect().left, _curMouse.y - _panels.at(i).second->getRect().top))
                {
                    _panels.at(i).second->closeButton->isClick = true;
                    _panels.at(i).second->closeButton->isHover = false;
                    break;
                }
                SDL_GetMouseState(&_mDragPosX, &_mDragPosY);
                _dragPanelName = _panels.at(i).first;
                break;
            }
        }
    }
}

void ZappyGui::Renderer::_mouseEventHold()
{
    int x = 0;
    int y = 0;
    ZappyGui::Rect rect;

    if (_prevMouse.lbIsPressed && _curMouse.lbIsPressed && _dragPanelName != "")
    {
        SDL_GetMouseState(&x, &y);
        x -= _mDragPosX;
        y -= _mDragPosY;
        SDL_GetMouseState(&_mDragPosX, &_mDragPosY);
        if (_panels.find(_dragPanelName) == _panels.end())
            return;
        rect = _panels[_dragPanelName]->getRect();
        _panels[_dragPanelName]->panelSetPosition(rect.left + x, rect.top + y);
        if (rect.left + x < 0)
            _panels[_dragPanelName]->panelSetPosition(0, rect.top);
        if (rect.left + x + rect.width > _width)
            _panels[_dragPanelName]->panelSetPosition(_width - rect.width, rect.top);
        if (rect.top + y < 0)
            _panels[_dragPanelName]->panelSetPosition(rect.left, 0);
        if (rect.top + y + rect.height > _height)
            _panels[_dragPanelName]->panelSetPosition(rect.left, _height - rect.height);
    }
}

void ZappyGui::Renderer::_mouseEventOnRelease()
{
    std::string name = "";

    if (_prevMouse.lbIsPressed && !_curMouse.lbIsPressed)
    {
        for (std::size_t i = 0; i < _panels.size(); i++)
        {
            if (_panels.at(i).second->closeButton != nullptr && _panels.at(i).second->closeButton->isClick)
            {
                if (_panels.at(i).second->closeButton->rect.isInRect(_curMouse.x - _panels.at(i).second->getRect().left, _curMouse.y - _panels.at(i).second->getRect().top))
                    name = _panels.at(i).first;
                _panels.at(i).second->closeButton->isClick = false;
            }
        }
        if (name != "")
            _panels.erase(name);
        _dragPanelName = "";
    }
}

void ZappyGui::Renderer::_mouseEventUpdate()
{
    if (!_prevMouse.lbIsPressed && !_curMouse.lbIsPressed)
    {
        for (std::size_t i = 0; i < _panels.size(); i++)
        {
            if (_panels.at(i).second->closeButton == nullptr)
                continue;
            if (_panels.at(i).second->closeButton->rect.isInRect(_curMouse.x - _panels.at(i).second->getRect().left, _curMouse.y - _panels.at(i).second->getRect().top)
                && !_panels.at(i).second->closeButton->isClick)
                _panels.at(i).second->closeButton->isHover = true;
            else
                _panels.at(i).second->closeButton->isHover = false;
        }
    }
}

void ZappyGui::Renderer::mouseEvent()
{
    _mouseEventOnClick();
    _mouseEventHold();
    _mouseEventOnRelease();
    _mouseEventUpdate();

    for (std::size_t i = 0; i < _panels.size(); i++)
    {
        if (_panels.at(i).second->closeButton != nullptr)
            _panels.at(i).second->closeButton->update();
    }
}
