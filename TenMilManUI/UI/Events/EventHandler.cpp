#include "EventHandler.h"

namespace TenUI{

long EventHandler::nextObjectID = 0;

EventHandler::EventHandler()
{
	objid = EventHandler::nextObjectID++;
}

EventHandler::~EventHandler()
{
}

}
