#include "TableInput_NewArch.h"
#include <TenMilManUI/UI/Managers/InputManager.h>
#include <TenMilManUI/UserInputs/Events/ZoomPointEvent.h>

#include <tr1/memory>

using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

#define	USER_NUM	4

namespace TenUI
{

//TODO: Make DeviceEventListener a string like UserInput::TableInput or something
TableInput_NewArch::TableInput_NewArch(std::string host, int port1, int port2):DeviceEventListener("TableInput_NewArch"){	
	
	for(int i = 0; i < USER_NUM; ++i)
	{
		uid.push_back(UserInput::getNextUserID());
	}
	/**
	 * Setting up the DeviceEventSubscriber
	 */	
	this->devSubscriber = new DeviceEventSubscriber(host, port1, port2);
	
	/**
	 * Adding all the DeviceEvents you are interested in
	 */
	//devSubscriber->registerEvent(new OverheadRawEvent(0,0,0,0,0,0,0));
	devSubscriber->registerEvent(new TouchRawEvent(*(new std::vector<point>())));
	devSubscriber->registerEvent(new ZoomEvent(0,*(new point)));
		
	/**
	 * Which class is a DeviceEventListener (which class implemented the process method, see below)
	 */
	devSubscriber->registerListener(this);
	
	/**
	 * Adding the events the TableInput_NewArch dispatches
	 */
	addEventType(PointEvent::MOVE_EVENT_TYPE); 				// overhead hovering
	addEventType(PointEvent::UP_EVENT_TYPE);
	addEventType(PointEvent::DOWN_EVENT_TYPE);
	addEventType(MultiPointEvent::MULTIPOINT_EVENT_TYPE);
	addEventType(ZoomPointEvent::ZOOM_EVENT_TYPE);
	//addEventType("MultiPointEvent");	// touch points
	//ZOOM addEventType(ZoomEvent::ZOOM_EVENT_TYPE);
}

TableInput_NewArch::~TableInput_NewArch(){}

void TableInput_NewArch::init(){}
bool TableInput_NewArch::update(){

	
	if(!eventQueue.empty())
	{
		DeviceEvent *devEvent = eventQueue.front();
		eventQueue.pop();
		
		//std::cout << "Received event: " << devEvent->getName() << std::endl;
		
		/*OverheadRawEvent *overheadRawEvent = dynamic_cast<OverheadRawEvent*>(devEvent);
		if(overheadRawEvent != 0){
			std::cout << "OverheadRawEvent:\n";
			std::cout << "hand(" << overheadRawEvent->getHandX() << ", " << overheadRawEvent->getHandY() << ")\t";
			std::cout << "edge(" << overheadRawEvent->getEdgeX() << ", " << overheadRawEvent->getEdgeY() << ")\t";
			std::cout << "id(" << overheadRawEvent->getID() 	  << ")\t";
			std::cout << "side(" << overheadRawEvent->getSide()  << ")\t";
			std::cout << "type(" << overheadRawEvent->getType()  << ")\n";
		
			//dispatchEvent(shared_ptr<PointEvent>(new PointEvent(PointEvent::MOVE_EVENT_TYPE, (overheadRawEvent->getSide() > 0 ? uid[overheadRawEvent->getSide() - 1] : uid[0]), uiid, overheadRawEvent->getID(), (int)overheadRawEvent->getHandX(), (int)overheadRawEvent->getHandY(), false)));
		}*/
		
		TouchRawEvent *touchEvent = dynamic_cast<TouchRawEvent*>(devEvent);
		if(touchEvent != 0){
			//cout << "I have received a touchEvent" << endl;
			//std::cout << "TouchRawEvent:";
			
			shared_ptr<MultiPointEvent> multiPtEvt(new MultiPointEvent(0, uiid));
			
			for(unsigned int i=0; i< touchEvent->getPoints().size(); i++){
				string evtType = "UNKNOWN";
				point pt = touchEvent->getPoints().at(i);
				
				if(pt.type == POINT_BIRTH)
					evtType = PointEvent::DOWN_EVENT_TYPE;
				else if(pt.type == POINT_DEATH)
					evtType = PointEvent::UP_EVENT_TYPE;
				else if(pt.type == POINT_MOVE)
					evtType = PointEvent::MOVE_EVENT_TYPE;
				
				//PointEvent tmpEvt();
				shared_ptr<PointEvent> tmpEvt(new PointEvent(evtType, (pt.side > 0 ? uid[pt.side - 1] : uid[0]), uiid, pt.id, (int)pt.x, 768 - (int)pt.y, (pt.type == POINT_DEATH ? false : true)));
				
				//dispatchEvent(tmpEvt);
				//return true;
				
				multiPtEvt->addPointEvent(tmpEvt);
				
				//std::cout << "pt(" << pt.x << ", " << pt.y << ")\n";
				/*if(pt.x == 0 && pt.y == 0)
					std::cout << "\t";
				std::cout << "id(" << pt.id << ")\t";
				std::cout << "type(" << pt.type  << ")\t";
				std::cout << "side(" << pt.side << ")\n";*/
				
				
			}
			
			dispatchEvent(multiPtEvt);
			
		}
		
		ZoomEvent *zoomEvent = dynamic_cast<ZoomEvent*>(devEvent);
		if(zoomEvent != 0){
			/*std::cout << "ZoomEvent:\n";
			std::cout << "center(" << zoomEvent->getCenterX() << "," << zoomEvent->getCenterY() << ")\tdist(" << zoomEvent->getDistance() << ")\n";
*/
			//shared_ptr<MultiPointEvent> mpe(new MultiPointEvent(uid, uiid));
			//mpe->addPointEvent();
			
			dispatchEvent(
				shared_ptr<ZoomPointEvent>(
					new ZoomPointEvent( ZoomPointEvent::ZOOM_EVENT_TYPE , 
						2, uiid,0,
						(zoomEvent->isZoomOut()?-5:5)*zoomEvent->getDistance(), 
						zoomEvent->getCenterX(),768-zoomEvent->getCenterY() 
					)
				)
			);			
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

void TableInput_NewArch::display() {
	std::cout << "TableInput_NewArch(" << uiid << ")\n";
	for(unsigned int i = 0; i < uid.size(); ++i)
	std::cout << "\tuid[" << i << "] " << uid[i] << "\n";
	std::cout << "\n";
}

}
