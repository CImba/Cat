#include <Irrlicht.h>
 using namespace irr;

 int main()
 {
    IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(1280,720));
    if(!device)
        return 1;
    video::IVideoDriver* driver  = device->getVideoDriver();
    scene::ISceneManager* svm = device->getSceneManager();
    scene::IAnimatedMesh* cat = svm->getMesh("cat/cat.obj");
    if(!cat)
    {
        device->drop();
        return 2;
    }
    scene::IMeshSceneNode* node = svm->addMeshSceneNode(cat);
    if(node)
        node->setMaterialFlag(video::EMF_LIGHTING,false);
    svm->addCameraSceneNode(0,core::vector3df(0,2,3),core::vector3df(0,0,0));
    while(device->run())
    {
        driver->beginScene(true,true,video::SColor(255,0,0,255));
        svm->drawAll();
        driver->endScene();
    }
    device->drop();
     return 0;
 }
