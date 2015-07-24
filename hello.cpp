#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;

enum class Order {ASCENDING, DESCENDING};

int main(int argc, char **argv) {
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
                                          dimension2d<u32>(640, 480), 16,
                                          false, false, false, 0);
    if(!device)
        return 1;

    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    IGUIEnvironment *guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Hello world! This is the Irrlicht OpenGL renderer!",
                          rect<s32>(10, 10, 260, 30), true);

    IMeshSceneNode *wall = smgr->addCubeSceneNode();
    wall->setMaterialFlag(EMF_LIGHTING, false);
    wall->setMaterialTexture(0, driver->getTexture("./wall.jpg"));

    smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

    int i = 0;
    Order mode = Order::ASCENDING;
    while(device->run()) {
        driver->beginScene(true, true, SColor(0, i, i, i));
        if (mode == Order::ASCENDING)
            if (i >= 254) {
                mode = Order::DESCENDING;
                i--;
            } else {
                i++;
        } else {
            if (mode == Order::DESCENDING) {
                if (i <= 0) {
                    mode = Order::ASCENDING;
                    i++;
                } else {
                    i--;
                }
            }
        }


        wall->setRotation(wall->getRotation() + vector3df(0, 1, 0));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    device->drop();

    return 0;
}
