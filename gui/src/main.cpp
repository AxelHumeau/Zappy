/*
** EPITECH PROJECT, 2023
** basicOgreApp
** File description:
** main
*/

#include <ois/OIS.h>
#include "Renderer.hpp"

Ogre::ManualObject* createCubeMesh(Ogre::String name, Ogre::String matName) {

	Ogre::ManualObject* cube = new Ogre::ManualObject(name);
	cube->begin(matName);

	cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,0);
	cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,1);
	cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,1);
	cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,0);
	cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(1,0);
	cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,1);
	cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,1);
	cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(0,0);
	cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(0,1);
	cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(1,1);
	cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(1,0);
	cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(0,1);
	cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(1,1);
	cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(0,0);
	cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,0);
	cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,0);
	cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(1,0);
	cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(0,1);
	cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(1,1);
	cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(0,0);

	cube->triangle(0,1,2);		cube->triangle(3,1,0);
	cube->triangle(4,5,6);		cube->triangle(4,7,5);
	cube->triangle(8,9,10);		cube->triangle(10,7,8);
	cube->triangle(4,11,12);	cube->triangle(4,13,11);
	cube->triangle(14,8,12);	cube->triangle(14,15,8);
	cube->triangle(16,17,18);	cube->triangle(16,19,17);
	cube->end();

	return cube;

}

void createScene(Zappy::Renderer &renderer)
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
    Ogre::Light* light = renderer.getSceneManager()->createLight("SpotLight");
    light->setDiffuseColour(1, 1, 1);
    light->setSpecularColour(1, 1, 1);
    light->setType(Ogre::Light::LT_SPOTLIGHT);
    Ogre::SceneNode* lightNode = renderer.getSceneManager()->getRootSceneNode()->createChildSceneNode();
    light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    lightNode->attachObject(light);
    lightNode->setPosition(0, 0, 15);
    lightNode->setDirection(0, 0, -1);

    // also need to tell where we are
    Ogre::SceneNode* camNode = renderer.getSceneManager()->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 6);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    std::shared_ptr<Ogre::Camera> cam(renderer.getSceneManager()->createCamera("myCam"), Zappy::nop{});
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam.get());

    // and tell it to render into the main window
    renderer.registerCamera(cam);

    // finally something to render
    Ogre::Entity* ent = renderer.getSceneManager()->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = renderer.getSceneManager()->getRootSceneNode()->createChildSceneNode();
    node->lookAt(Ogre::Vector3(0, 0, 1), Ogre::Node::TS_PARENT);
    node->attachObject(ent);

    Ogre::MaterialPtr myMat = Ogre::MaterialManager::getSingleton().create("myMat", "General");
    myMat->setReceiveShadows(false);
    myMat->getTechnique(0)->setLightingEnabled(true);
    // myMat->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,1);
    // myMat->getTechnique(0)->getPass(0)->setAmbient(0,0,0);
    // myMat->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,0);

    Ogre::SceneNode* node2 = renderer.getSceneManager()->getRootSceneNode()->createChildSceneNode();
    node2->setPosition(0,0,8);
    node2->roll(Ogre::Radian(0.785398f));
    node2->pitch(Ogre::Radian(0.349066f));
    node2->yaw(Ogre::Radian(0.785398f));
    node2->attachObject(createCubeMesh("Cube", "myMat"));
    renderer.render();
}

int main(void) {
    Zappy::Renderer renderer(std::string("Zappy"));
    createScene(renderer);
    return 0;
}