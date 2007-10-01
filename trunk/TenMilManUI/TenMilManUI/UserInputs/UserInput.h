// header file for the user input.
// this is extended by tableinput and sdlmouseinput.
// you can choose to run in either mouse-mode or
// table-mode by commenting/uncommenting 1 of 2 lines
// in main.cpp

#ifndef USERINPUT_H
#define USERINPUT_H

struct InputData{
	int x;
	int y;
	int id;
	bool pressed;
	bool select;
};

class UserInput {
protected:
	static bool isCreated;
	static UserInput* inst;
	InputData indata;
	bool quit;

	UserInput(){
		UserInput::isCreated = true;
		indata.x = 0;
		indata.y = 0;
		indata.id = 0;
		indata.pressed = false;
		quit = false;
	}

	virtual ~UserInput(){

	}

public:
	static UserInput* createInstance();
	static UserInput* instance();

	virtual bool update()=0;	
	
	virtual int getX(){
		return indata.x;
	}
	
	virtual int getY(){
		return indata.y;
	}

	virtual bool isPressed(){
		return indata.pressed;
	}
	
	virtual bool isSelect(){
		return indata.select;
	}

	virtual bool isQuit(){
		return quit;
	}
};

#endif
