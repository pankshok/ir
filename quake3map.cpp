#include <irrlicht.h>

using namespace irr;


int main(int argc, char **argv, char **env)
{
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
                                          core::dimension2d<u32>(640, 480));

    if (device == 0)
        return 1;

    video::IVideoDriver *driver = device->getVideoDriver();
    scene::ISceneManager *smgr = device->getSceneManager();

    // loading map
    device->getFileSystem()->addFileArchive("./map-20kdm2.pk3");
    scene::IAnimatedMesh *mesh = smgr->getMesh("20kdm2.bsp");
    scene::ISceneNode *level = 0;

    if (mesh)
        level = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);

    // some translations
    if (level)
        level->setPosition(core::vector3df(-1300, -144, -1249));

    smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);

    while(device->run()) {
        if (device->isWindowActive()) {
            driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
            smgr->drawAll();
            driver->endScene();
        } else {
            device->yield();
        }
    }

    device->drop();
    return 0;
}
