#ifndef TABLEINPUT_NEWARCH_H_
#define TABLEINPUT_NEWARCH_H_


#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>

#include <libsocketcpp/tcpsocket.h>

#include <DeviceCore/DeviceEventSubscriber/DeviceEventSubscriber.h>
#include <DeviceCore/DeviceEvent/DeviceEventListener/DeviceEventListener.h>

//#include <Overhead_InputDevice/DeviceEvents/OverheadRawEvent.h>
#include <Touch_InputDevice/DeviceEvents/TouchRawEvent.h>
#include <Touch_InputDevice/DeviceEvents/ZoomEvent.h>

//#include "../Graphics/Vector/Line.h"

//#include "UserInput.h"
#include <TenMilManUI/UserInputs/UserInput.h>
//#include "MultiInput.h"
//#include "BasicInput.h"
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>

namespace TenUI
{

	class TableInput_NewArch : public UserInput, public DeviceEventListener {
	private:
		DeviceEventSubscriber *devSubscriber;
		std::queue<DeviceEvent *> eventQueue;
		std::vector<unsigned long> uid;
		
	public:
		TableInput_NewArch(std::string host, int port1, int port2);
		virtual ~TableInput_NewArch();

		virtual bool hoverCapable();
		virtual void init();
		virtual bool update();
		
		//Line *horzBar, *vertBar;
		
		//virtual int getX(int index);
		//virtual int getY(int index);
		//virtual bool isPressed(int index);	
	
		virtual void process(DeviceEvent *);
		
		// DEBUG
		void display();
	};

}

#endif /*TABLEINPUT_NEWARCH_H_*/
