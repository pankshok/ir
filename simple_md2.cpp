#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;

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

    vector3df processObjectMovement(ISceneNode *node)
    {
        const u32 DWATEVER = 3.f;
        vector3df position = node->getPosition();

        if (IsKeyDown(KEY_KEY_W))
            position.Y += DWATEVER;
        else if (IsKeyDown(KEY_KEY_S))
            position.Y -= DWATEVER;

        if (IsKeyDown(KEY_KEY_A))
            position.X -= DWATEVER;
        else if (IsKeyDown(KEY_KEY_D))
            position.X += DWATEVER;

        return position;
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

    IMeshSceneNode *wall = smgr->addCubeSceneNode();
    if (wall) {
        wall->setPosition(vector3df(0, 0, 30));
        wall->setMaterialFlag(EMF_LIGHTING, false);
        wall->setMaterialTexture(0, driver->getTexture("./wall.jpg"));
    }

    IMeshSceneNode *sydney = smgr->addMeshSceneNode(smgr->getMesh("./sydney.md2"));
    if (sydney) {
        sydney->setMaterialFlag(EMF_LIGHTING, false);
        sydney->setMaterialTexture(0, driver->getTexture("./sydney.bmp"));
    }

    ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS();
    camera->setPosition(vector3df(0, 0, -50));
    device->getCursorControl()->setVisible(false);

    const u32 DWATEVER = 5.f;
    while(device->run()) {
        driver->beginScene(true, true, SColor(0, 0, 0, 0));

        vector3df camera_position = receiver.processObjectMovement(camera);
        camera->setPosition(camera_position);


        smgr->drawAll();

        driver->endScene();
    }

    device->drop();

    return 0;
}
