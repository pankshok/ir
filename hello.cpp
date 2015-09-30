#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;

enum class Order {ASCENDING, DESCENDING};


class MyEventReceiver : public IEventReceiver
{
public:
    virtual bool OnEvent(const SEvent &event)
    {
        if (event.EventType == EET_KEY_INPUT_EVENT) {
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        }

        return false;
    }

    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    MyEventReceiver()
    {
        for (u32 i=0; i < KEY_KEY_CODES_COUNT; ++i) {
            KeyIsDown[i] = false;
        }
    }

private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


int main(int argc, char **argv) {
    MyEventReceiver receiver;
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
                                          dimension2d<u32>(640, 480), 16,
                                          false, false, false, &receiver);
    if(!device)
        return 1;

    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");


    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    IGUIEnvironment *guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Hello world! This is the Irrlicht OpenGL renderer!",
                          rect<s32>(10, 10, 260, 30), true);

    IMeshSceneNode *wall = smgr->addCubeSceneNode();
    IAnimatedMesh *mesh1 = smgr->getMesh("untitled.obj");
    ISceneNode *node1 = 0;

    if(mesh1) {
        node1 = smgr->addOctreeSceneNode(mesh1->getMesh(0), 0, -1, 1024);
        node1->setMaterialFlag(EMF_LIGHTING, false);
    }

    if (wall) {
        wall->setPosition(core::vector3df(0, 0, 30));
        wall->setMaterialFlag(EMF_LIGHTING, false);
        wall->setMaterialTexture(0, driver->getTexture("./wall.jpg"));
    }

    IMeshSceneNode *actor = smgr->addSphereSceneNode();
    if (actor) {
        actor->setMaterialFlag(video::EMF_LIGHTING, false);
        actor->setMaterialTexture(0, driver->getTexture("./wall.jpg"));
        ISceneNodeAnimator *anim = smgr->createFlyCircleAnimator(vector3df(0, 0, 30), 20.0f);
        if (anim) {
            actor->addAnimator(anim);
            anim->drop();
        }
    }

//    smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));
    ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);
    camera->addChild(wall);

    int i = 0;
    Order mode = Order::ASCENDING;
    const u32 DWATEVER = 5.f;
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

        vector3df wall_position = wall->getPosition();

        if (receiver.IsKeyDown(KEY_KEY_W))
            wall_position.Y += DWATEVER;
        else if (receiver.IsKeyDown(KEY_KEY_S))
            wall_position.Y -= DWATEVER;

        if (receiver.IsKeyDown(KEY_KEY_A))
            wall_position.X -= DWATEVER;
        else if (receiver.IsKeyDown(KEY_KEY_D))
            wall_position.X += DWATEVER;


        wall->setPosition(wall_position);


        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    device->drop();

    return 0;
}
