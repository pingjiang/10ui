// header file for table input.  you can change between
// mouse input and table input in the main.cpp file by
// commenting out one of the two initialization lines.

#ifndef TABLEINPUT_H
#define TABLEINPUT_H

//#include "UserInput.h"
#include "BasicInput.h"
#include "../TenMilManUI.h"

namespace TenUI {

struct tmpEvent {
	int x,y;
	char type;
};

//class TableInput : UserInput {
class TableInput : public BasicInput {
protected:
	//static bool isCreated;
	//static UserInput* inst;
	
	long fid, uid; // "finger" id, user id (table side)

	// data now in BasicInput
	int x,y;
	bool pressed;
	bool quit;
	
public:
	TableInput(long muid = 0) : BasicInput(), uid(muid){
		UI_type = UserInput::TABLE_INPUT;
		x = -1;
		y = -1;
		fid = 0;
		//uid = 0; // TODO: update for multiple users
		quit = false;
	}
	
	static UserInput* createInstance();
	static UserInput* createInstance(long muid);
	//static UserInput* instance();
	
	virtual void init() {}
	virtual bool update(){

		tmpEvent event;
		if(x + 1 < 640)
		event.x = x + 1;
		else
			event.x = 0;
		
		if(y+1 < 480)
		event.y = y + 1;
		else
			event.y = 0;
		
		/*event.x = 500;
		event.y = 320;*/
		event.type = 'm';
		
		//select = false;
		
		x = event.x;
		y = event.y;
					
		if(event.type == 'm')
		{	
		}
		if(event.type == 'd' && !pressed)
		{
			pressed = true;
		}
		if(event.type == 'u')
		{
			pressed = false;
			//select = true;
		}

		return true;
	}
	
	virtual int getX() { return x; }
	virtual int getY() { return y; }
	virtual bool isPressed() { return pressed; }
	//virtual bool isSelect() { return select; }
	
	virtual bool isQuit() { return quit; }
};


}

#endif
