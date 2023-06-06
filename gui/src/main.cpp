/*
** EPITECH PROJECT, 2023
** basicOgreApp
** File description:
** main
*/

#include <OgreWindowEventUtilities.h>
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"

void createScene(ZappyGui::Renderer &renderer)
{
    // Directional light
    // Ogre::Light* directionalLight = scnMgr->createLight("DirectionalLight");
    // directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    // directionalLight->setDiffuseColour(Ogre::ColourValue(1, 0, 0));
    // directionalLight->setSpecularColour(Ogre::ColourValue(1, 0, 0));
    // Ogre::SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    // directionalLightNode->attachObject(directionalLight);
    // directionalLightNode->setPosition(0, 0, 15);
    // directionalLightNode->setDirection(Ogre::Vector3(0, 0, -1));

    // without light we would just get a black screen
    ZappyGui::Light light2(renderer.getSceneManager(), "light2", Ogre::Light::LT_SPOTLIGHT);
    light2.setDiffuseColour(1, 1, 1);
    light2.setSpecularColour(1, 1, 1);
    light2.setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    light2.setPosition(0, 0, 15);
    light2.setDirection(0, 0, -1);

    // also need to tell where we are

    // create the camera
    ZappyGui::Camera cam(renderer.getSceneManager(), "myCam");
    cam.setNearClipDistance(0.05); // specific to this sample
    cam.setAutoAspectRatio(true);
    cam.setPosition(0, 0, 0);
    cam.lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // and tell it to render into the main window
    renderer.registerCamera(cam.getCamera());

    // finally something to render
    ZappyGui::GameObject jerome(renderer.getSceneManager(), "hamster.mesh");
    jerome.setPosition(0, 0, -5);
    jerome.lookAt(Ogre::Vector3(10, 10, 0), Ogre::Node::TS_PARENT);

    Ogre::MaterialPtr myMat = Ogre::MaterialManager::getSingleton().create("myMat", "General");
    myMat->setReceiveShadows(false);
    myMat->getTechnique(0)->setLightingEnabled(true);

    while (!renderer.isDone())
    {
        renderer.event();
        jerome.setRotation(Ogre::Radian(0.01f), Ogre::Radian(-0.001f), Ogre::Radian(0.05f));
        renderer.renderOneFrame();
    }
}

int main(void) {
    ZappyGui::Renderer renderer(std::string("Zappy"), 800*1.5, 600*1.5);
    createScene(renderer);
    return 0;
}
