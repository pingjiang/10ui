// header file for the user input.
// this is extended by tableinput and sdlmouseinput.
// you can choose to run in either mouse-mode or
// table-mode by commenting/uncommenting 1 of 2 lines
// in main.cpp

#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <iostream>
#include <TenMilManUI/UI/Events/EventDispatcher.h>

#include "UserInput_Globals.h"

using namespace std;

namespace TenUI {
	
	class UserInput : public EventDispatcher {
	private:
		static UserInputID_Type nextUIID;
		static UserID_Type 		nextUID;		
				
	protected:
		UserInput() : uiid(UserInput::nextUIID++), quit(false) {}
		virtual ~UserInput() {}
		
		// common across all UserInputs
		unsigned long uiid;
		bool quit;
	
		static UserID_Type getNextUserID();
	public:
		virtual void init() = 0;
		virtual bool update() = 0;
		
		UserInputID_Type getUserInputID()	{ return uiid; }
		virtual bool isQuit() { return quit; }
	
	};

}

#endif
