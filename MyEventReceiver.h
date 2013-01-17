#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H
#include <Irrlicht.h>
using namespace irr;

class MyEventReceiver : public IEventReceiver
{
    public:
        MyEventReceiver();
        ~MyEventReceiver();

        virtual bool OnEvent(const SEvent& event);
        virtual bool IsKeyDown(EKEY_CODE keyCode) const;
        core::position2di getPosition();
        bool isMoved();
        void movedIs(bool mov);
        core::position2df get_coord();
    private:
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif // MYEVENTRECEIVER_H
