#include <iostream>
#include "Manager.h"

namespace TenUI{

Manager::Manager()
{ 
}

Manager::~Manager()
{
}

bool Manager::registerObj(UIComponent* obj)
{
	// Try to find obj
	std::map<long, UIComponent*>::iterator i = registeredObjects.find(obj->getObjectID());	

	// Not found -> add
	if(i == registeredObjects.end())
	{
		registeredObjects[obj->getObjectID()] = obj;
		return true;
	}

	// Already present
	return false;
}

void Manager::displayRegisteredObjects()
{
	for(std::map<long, UIComponent*>::iterator map_iter = registeredObjects.begin(); map_iter != registeredObjects.end(); ++map_iter)
		std::cout << "(" << map_iter->first << "," << map_iter->second << ")\n";
	std::cout << "\n";
}

bool Manager::update()
{
	return true;
}

}
