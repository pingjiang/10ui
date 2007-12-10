#include "Event.h"

namespace TenUI{

	Event::Event(string _type):type(_type){}
	Event::~Event(){}
	
	const string& Event::getType(){
		return type;
	}
	
}
