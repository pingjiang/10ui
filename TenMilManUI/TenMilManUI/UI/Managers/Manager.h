#ifndef MANAGER_H_
#define MANAGER_H_

#include "../Core/UIComponent.h"
#include "../../UserInputs/UserInput.h"
#include <map>

namespace TenUI{
class Manager
{
public:
	Manager();
	virtual ~Manager();
	
	bool registerObj(UIComponent*);
	void displayRegisteredObjects();
	
	virtual void init() = 0;
	virtual bool update() = 0;
	
protected:
	
	std::map<long,UIComponent*> registeredObjects;
};

}

#endif /*MANAGER_H_*/
