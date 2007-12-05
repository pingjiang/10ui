#include "TableInput_NewArch.h"
#include <TenMilManUI/UI/Managers/InputManager.h>

namespace TenUI
{

//TODO: Make DeviceEventListener a string like UserInput::TableInput or something
TableInput_NewArch::TableInput_NewArch(std::string host, int port1, int port2):DeviceEventListener("TableInput_NewArch"){	
	/**
	 * Setting up the DeviceEventSubscriber
	 */	
	this->devSubscriber = new DeviceEventSubscriber(host, port1, port2);
	
	/**
	 * Adding all the DeviceEvents you are interested in
	 */
	devSubscriber->registerEvent(new OverheadRawEvent(0,0,0,0,0,0,0));
	devSubscriber->registerEvent(new TouchRawEvent(*(new std::vector<point>())));
		
	/**
	 * Which class is a DeviceEventListener (which class implemented the process method, see below)
	 */
	devSubscriber->registerListener(this);
	
	//std::cout << "this:\t" << this << "\n";
	
	//InputManager::getInputs()->insert((UserInput*)this);
}

TableInput_NewArch::~TableInput_NewArch(){}

void TableInput_NewArch::init(){}
bool TableInput_NewArch::update(){

	if(!eventQueue.empty())
	{
		DeviceEvent *devEvent = eventQueue.front();
		eventQueue.pop();
		
		/*OverheadRawEvent *overheadRawEvent = dynamic_cast<OverheadRawEvent*>(devEvent);
		if(overheadRawEvent != 0){
			std::cout << "OverheadRawEvent:\n";
			std::cout << "hand(" << overheadRawEvent->getHandX() << ", " << overheadRawEvent->getHandY() << ")\t";
			std::cout << "edge(" << overheadRawEvent->getEdgeX() << ", " << overheadRawEvent->getEdgeY() << ")\t";
			std::cout << "id(" << overheadRawEvent->getID() 	  << ")\t";
			std::cout << "side(" << overheadRawEvent->getSide()  << ")\t";
			std::cout << "type(" << overheadRawEvent->getType()  << ")\n";
		}*/
		
		TouchRawEvent *touchEvent = dynamic_cast<TouchRawEvent*>(devEvent);
		if(touchEvent != 0){
			//cout << "I have received a touchEvent" << endl;
			std::cout << "TouchRawEvent:\n";
			for(unsigned int i=0; i< touchEvent->getPoints().size(); i++){
				
				point pt = touchEvent->getPoints().at(i);
				std::cout << "pt(" << pt.x << ", " << pt.y << ")\t";
				if(pt.x == 0 && pt.y == 0)
					std::cout << "\t";
				std::cout << "id(" << pt.id << ")\t";
				std::cout << "type(" << pt.type  << ")\t";
				std::cout << "side(" << pt.side << ")\n";
			}
			
		}
		
		/*if(overheadRawEvent == 0 && touchEvent == 0){
			cout << "UNHANDLED EVENT CASE" << endl;
		}*/
	}
	return true;
}
		
//int TableInput_NewArch::getX(int index){ return 0; }
//int  TableInput_NewArch::getY(int index){ return 0; }
//bool  TableInput_NewArch::isPressed(int index){ return false; }
//bool  TableInput_NewArch::isQuit(){ return false; }


/**
 * This method will be called when a DeviceEvent is received.
 */
void TableInput_NewArch::process(DeviceEvent *devEvent){
	
	eventQueue.push(devEvent);
	return;
	
	/*OverheadRawEvent *overheadRawEvent = dynamic_cast<OverheadRawEvent*>(devEvent);
	if(overheadRawEvent != 0){
		std::cout << "OverheadRawEvent (HandX, HandY, EdgeX, EdgeY, ID, Side, Type) : (";
		std::cout << overheadRawEvent->getHandX() << ", ";
		std::cout << overheadRawEvent->getHandY() << ", ";
		std::cout << overheadRawEvent->getEdgeX() << ", ";
		std::cout << overheadRawEvent->getEdgeY() << ", ";
		std::cout << overheadRawEvent->getID() 	  << ", ";
		std::cout << overheadRawEvent->getSide()  << ", ";
		std::cout << overheadRawEvent->getType()  << ")" << std::endl;
	}
	
	TouchRawEvent *touchEvent = dynamic_cast<TouchRawEvent*>(devEvent);
	if(touchEvent != 0){
		cout << "I have received a touchEvent" << endl;
		
		for(unsigned int i=0; i< touchEvent->getPoints().size(); i++){
			std::cout << "TouchRawEvent : (";
			point pt = touchEvent->getPoints().at(i);
			std::cout << pt.x << ", ";
			std::cout << pt.y << ", ";
			std::cout << pt.id << ", ";
			std::cout << pt.type  << ",";
			std::cout << pt.side << endl;
		}
		
	}
	else{
		cout << "I received an event which was not an overhead nor a touch event" << endl;
	}*/
}

}
