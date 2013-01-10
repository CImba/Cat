#include <Irrlicht.h>
#include "MyEventReceiver.h"
 using namespace irr;

 int main()
 {
    MyEventReceiver receiver;
    IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(1280,720),32,false,false,true,&receiver);
    if(!device)
        return 1;
    video::IVideoDriver* driver  = device->getVideoDriver();
    scene::ISceneManager* svm = device->getSceneManager();
    scene::IAnimatedMesh* cat = svm->getMesh("cat/cat.b3d");
    if(!cat)
    {
        device->drop();
        return 2;
    }
    //add simple plane
    scene::IMesh* plane = svm->addHillPlaneMesh("plane",core::dimension2d<f32>(200,200),core::dimension2d<u32>(20,20));
    scene::IMeshSceneNode* planeNode = svm->addMeshSceneNode(plane);
    planeNode->setMaterialFlag(video::EMF_LIGHTING,false);
    planeNode->setMaterialTexture(0,driver->getTexture("texture/grass.jpg"));
    scene::IMeshSceneNode* node = svm->addMeshSceneNode(cat);
    if(node)
        node->setMaterialFlag(video::EMF_LIGHTING,false);
    scene::ICameraSceneNode* camera = svm->addCameraSceneNode(node,core::vector3df(1,5,8.5),core::vector3df(0,0,0));
    node->setRotation(core::vector3df(0,-90,0));
    while(device->run())
    {
        driver->beginScene(true,true,video::SColor(255,0,0,255));
        svm->drawAll();
        if(receiver.IsKeyDown(KEY_KEY_W))
        {
             node->setPosition(node->getPosition()+core::vector3df(1,0,0));
        }

        if(receiver.IsKeyDown(KEY_KEY_S))
        {
            node->setPosition(node->getPosition()+core::vector3df(-1,0,0));
        }

        if(receiver.IsKeyDown(KEY_KEY_A))
        {
             node->setPosition(node->getPosition()+core::vector3df(0,0,1));
        }

        if(receiver.IsKeyDown(KEY_KEY_D))
        {
            node->setPosition(node->getPosition()+core::vector3df(0,0,-1));
        }

        //camera
        camera->setTarget(node->getPosition());

        if(receiver.IsKeyDown(KEY_ESCAPE))
        {
            exit(1);
        }

        driver->endScene();
    }
    device->drop();
     return 0;
 }
