// header file for the user input.
// this is extended by tableinput and sdlmouseinput.
// you can choose to run in either mouse-mode or
// table-mode by commenting/uncommenting 1 of 2 lines
// in main.cpp

#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <iostream>
//#include "InputManager.h"

using namespace std;

namespace TenUI {

class UserInput {	
protected:
	UserInput(){}
	virtual ~UserInput() {}
	
	char UI_type;
	char UI_data;

public:
	virtual void init() = 0;
	virtual bool update() = 0;
	
	char getType()			{ return UI_type; }
	char getDataFormat()	{ return UI_data; }

	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual bool isPressed() = 0;	
	virtual bool isQuit() = 0;

	static char MOUSE_INPUT;
	static char TABLE_INPUT;
	
	static char BASIC_DATA;
	static char GESTURE_DATA;
	static char REALTIME_DATA;
};

}

#endif
