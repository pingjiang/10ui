#ifndef ITENMILMANUIAPP_H_
#define ITENMILMANUIAPP_H_

#include <string>

#include "TenMilManUI.h"
#include "TenMilManUI_Enums.h"
#include "UserInputs/UserInput.h"

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
			
			virtual char* 		getName() = 0; 
			virtual int 		getScreenWidth() = 0;
			virtual int 		getScreenHeight() = 0;
			virtual int 		getScreenBPP() = 0;
			virtual TenUI::SCREEN_OPTION 	getScreenOptions() = 0;
			//virtual UserInput* 	getUserInput() = 0;
			virtual void		initializeUserInput() = 0;
			virtual string		getFontDirectory() =0;
			
			virtual ~ITenMilManUIApp(){}
	};
}

#endif /*ITENMILMANUIAPP_H_*/
