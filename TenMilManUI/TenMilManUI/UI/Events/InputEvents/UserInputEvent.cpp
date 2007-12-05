#include "UserInputEvent.h"

namespace TenUI {

const string UserInputEvent::QUIT_EVENT_TYPE = "QUIT_INPUT_EVENT";

UserInputEvent::UserInputEvent(string _type, unsigned long _uid) : Event(_type), uid(_uid)
{
}

UserInputEvent::~UserInputEvent()
{
}

}
