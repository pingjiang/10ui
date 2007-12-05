#ifndef MULTIINPUT_H_
#define MULTIINPUT_H_

#include "UserInput.h"
#include <vector>

using namespace std;

namespace TenUI
{

class MultiInput : public UserInput
{
protected:
	vector<int> x;
	vector<int> y;
	vector<bool> pressed;
	
public:
	MultiInput();
	virtual ~MultiInput();
	
	virtual int getX(int index)			{ return x[index]; }
	virtual int getY(int index)			{ return y[index]; }
	virtual bool isPressed(int index)	{ return pressed[index]; }
	virtual int size()					{ return x.size(); } // == y.size() == pressed.size()
};

}

#endif /*MULTIINPUT_H_*/
