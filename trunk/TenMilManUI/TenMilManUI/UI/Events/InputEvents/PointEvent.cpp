#include "PointEvent.h"

namespace TenUI{

const string PointEvent::MOVE_EVENT_TYPE = "MOVE_EVENT_TYPE";
const string PointEvent::UP_EVENT_TYPE= "UP_EVENT_TYPE";
const string PointEvent::DOWN_EVENT_TYPE= "DOWN_EVENT_TYPE";


PointEvent::PointEvent(string _type, unsigned long _uid, int _x, int _y, bool _pressed) : UserInputEvent(_type,_uid), x(_x), y(_y), pressed(_pressed)
{
}

PointEvent::~PointEvent()
{
}

}
