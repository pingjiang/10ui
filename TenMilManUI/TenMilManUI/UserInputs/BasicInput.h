#ifndef BASICINPUT_H_
#define BASICINPUT_H_

#include "UserInput.h"

namespace TenUI
{

class BasicInput : public UserInput
{
protected:
	int x,y;
	bool pressed;
	
public:
	BasicInput();
	virtual ~BasicInput();
	
	virtual int getX()			{ return x; }
	virtual int getY()			{ return y; }
	virtual bool isPressed()	{ return pressed; }	
	
};

}

#endif /*BASICINPUT_H_*/
