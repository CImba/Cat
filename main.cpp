#include <Irrlicht.h>
#include "MyEventReceiver.h"
#include <vector>
#include <time.h>
using namespace std;
 using namespace irr;

    int resolutionX=1280;
    int resolutionY=720;

void walk(MyEventReceiver* receiver,scene::IAnimatedMeshSceneNode* character,scene::ICameraSceneNode* camera);

 int main()
 {

    MyEventReceiver receiver;
    IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(resolutionX,resolutionY),32,false,false,true,&receiver);
    if(!device)
        return 1;
    video::IVideoDriver* driver  = device->getVideoDriver();
    gui::IGUIEnvironment* gui = device->getGUIEnvironment();
    scene::ISceneManager* svm = device->getSceneManager();
    scene::IAnimatedMesh* cat = svm->getMesh("cat/cat.b3d");

    if(!cat)
    {
        device->drop();
        return 2;
    }
    //add simple plane
    scene::IMesh* plane = svm->addHillPlaneMesh("plane",core::dimension2d<f32>(10,10),core::dimension2d<u32>(200,200),0,0,core::dimension2d<f32>(0,0),core::dimension2d<f32>(200,200));
    scene::IMeshSceneNode* planeNode = svm->addMeshSceneNode(plane);
    planeNode->setMaterialTexture(0,driver->getTexture("texture/grass.jpg"));
    scene::IAnimatedMeshSceneNode* node = svm->addAnimatedMeshSceneNode(cat);
    scene::ICameraSceneNode* camera = svm->addCameraSceneNodeFPS();
    node->setRotation(core::vector3df(0,-90,0));
    device->getCursorControl()->setVisible(false);
    //попытаемся добавить анимацию
	scene::ISceneNodeAnimator* anim = svm->createSceneNodeAnimator("move",node);
    node->addAnimator(anim);
    node->setAnimationSpeed(5);
    //и освещение...
    scene::ILightSceneNode* sun = svm->addLightSceneNode(0,core::vector3df(0,100,0));
    sun->enableCastShadow();
    //ну а в конце попробуем сделать что нибудь из GUI

    //а еще можно добавить деревьев
    vector<scene::IMeshSceneNode*>trees;
    srand(time(0));
    for(int i=0;i<100;i++)
    {
      trees.push_back(svm->addMeshSceneNode(svm->getMesh("models/tree/Tree1.b3d"),0,0,core::vector3df(rand()%200,0,rand()%200)));
      trees[i]->setScale(core::vector3df(10,10,10));
      trees[i]->setMaterialFlag(video::EMF_LIGHTING,false);
    }

    while(device->run())
    {
        driver->beginScene(true,true,video::SColor(255,0,0,255));
        svm->drawAll();
        //movement
        walk(&receiver,node,camera);
        //camera

        camera->setPosition(node->getPosition()+core::vector3df(-10 ,5,-1.5));

        if(receiver.IsKeyDown(KEY_ESCAPE))
        {
            exit(1);
        }

        driver->endScene();
    }
    device->drop();
     return 0;
 }
void walk(MyEventReceiver* receiver,scene::IAnimatedMeshSceneNode* character,scene::ICameraSceneNode* camera)
{
    if(receiver->IsKeyDown(KEY_KEY_W))
        {
             character->setPosition(character->getPosition()+core::vector3df(1,0,0));
             camera->setTarget(character->getPosition()+core::vector3df(0 ,5,-5));

        }

        if(receiver->IsKeyDown(KEY_KEY_S))
        {
            character->setPosition(character->getPosition()+core::vector3df(-1,0,0));
            camera->setTarget(character->getPosition()+core::vector3df(0 ,5,-5));
        }

        if(receiver->IsKeyDown(KEY_KEY_A))
        {
             character->setPosition(character->getPosition()+core::vector3df(0,0,1));
             camera->setTarget(character->getPosition()+core::vector3df(0 ,5,-5));
        }

        if(receiver->IsKeyDown(KEY_KEY_D))
        {
            character->setPosition(character->getPosition()+core::vector3df(0,0,-1));
            camera->setTarget(character->getPosition()+core::vector3df(0 ,5,-5));
        }
}

