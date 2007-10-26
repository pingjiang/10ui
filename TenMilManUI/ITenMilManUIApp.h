#ifndef ITENMILMANUIAPP_H_
#define ITENMILMANUIAPP_H_

#include <string>

#include <TenMilManUI/TenMilManUI.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UserInputs/UserInput.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>

using std::string;

class TenMilManUI;

namespace TenUI {

	enum APPEXCEPTIONS { APPEXCEPTION_TENMILMANUIAPP_INIT_FAILED };

	class ITenMilManUIApp {
		private:		
		protected:
		public:
			ITenMilManUIApp();
			
			virtual void init() throw(int) = 0;
			virtual void update_preframe() throw(APPEXCEPTIONS) = 0;
			virtual void update_frame() throw(APPEXCEPTIONS) = 0;
			virtual void deinit() throw(APPEXCEPTIONS) = 0;
			
			virtual GraphicsOptions* getGraphicsOptions() = 0;
			virtual IGraphics* getGraphics() = 0;
			virtual UserInput* 	getUserInput() = 0;
			//virtual void		initializeUserInput() = 0;
			
			virtual ~ITenMilManUIApp(){}
	};
}

#endif /*ITENMILMANUIAPP_H_*/
