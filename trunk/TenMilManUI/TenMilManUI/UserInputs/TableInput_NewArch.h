#ifndef TABLEINPUT_NEWARCH_H_
#define TABLEINPUT_NEWARCH_H_


#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>

#include <libsocketcpp/tcpsocket.h>

#include <DeviceCore/DeviceEventSubscriber/DeviceEventSubscriber.h>
#include <DeviceCore/DeviceEvent/DeviceEventListener/DeviceEventListener.h>

#include <Overhead_InputDevice/DeviceEvents/OverheadRawEvent.h>
#include <Touch_InputDevice/DeviceEvents/TouchRawEvent.h>

//#include "../Graphics/Vector/Line.h"

#include "UserInput.h"
//#include "MultiInput.h"
//#include "BasicInput.h"

namespace TenUI
{

	class TableInput_NewArch : public UserInput, public DeviceEventListener {
	private:
		DeviceEventSubscriber *devSubscriber;
		std::queue<DeviceEvent *> eventQueue;
		
	public:
		TableInput_NewArch(std::string host, int port1, int port2);
		virtual ~TableInput_NewArch();
		
		virtual void init();
		virtual bool update();
		
		//Line *horzBar, *vertBar;
		
		//virtual int getX(int index);
		//virtual int getY(int index);
		//virtual bool isPressed(int index);	
	
		virtual void process(DeviceEvent *);
	};

}

#endif /*TABLEINPUT_NEWARCH_H_*/
