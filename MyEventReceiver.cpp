#include "MyEventReceiver.h"

MyEventReceiver::MyEventReceiver()
{
    for(u32 i=0;i<KEY_KEY_CODES_COUNT;++i)
        KeyIsDown[i]=false;

}

MyEventReceiver::~MyEventReceiver()
{
    //dtor
}
 bool MyEventReceiver::OnEvent(const SEvent& event)
{
    if(event.EventType == EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key]=event.KeyInput.PressedDown;

return false;
}

bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

