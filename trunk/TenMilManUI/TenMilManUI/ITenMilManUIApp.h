#ifndef ITENMILMANUIAPP_H_
#define ITENMILMANUIAPP_H_

#include <string>

#include "TenMilManUI.h"
#include "TenMilManUI_Enums.h"
#include "UserInputs/UserInput.h"

using std::string;

namespace TenMilManUI_CORE {
	class TenMilManUI;
}

namespace TenMilManUI_APP {

	enum APPEXCEPTIONS { APPEXCEPTION_TENMILMANUIAPP_INIT_FAILED };

	class ITenMilManUIApp {
		private:
			//TenMilManUI_CORE::TenMilManUI* tenui;		
			
		protected:
			/*TenMilManUI_CORE::TenMilManUI* getTenUI(){
				return tenui;
			}*/
		public:
			ITenMilManUIApp();
			//void setTenUI(TenMilManUI_CORE::TenMilManUI *tui);
			
			// must setup 
			virtual void init() throw(int) = 0;
			virtual void update_preframe() throw(int) = 0;
			virtual void update_frame() throw(int) = 0;
			virtual void deinit() throw(int) = 0;
			
			virtual char* 			getName() = 0; 
			virtual int 			getScreenWidth() = 0;
			virtual int 			getScreenHeight() = 0;
			virtual int 			getScreenBPP() = 0;
			virtual TenMilManUI_CORE::SCREEN_OPTION 	getScreenOptions() = 0;
			virtual UserInput* 		getUserInput() = 0;
			virtual string			getFontDirectory() =0;
			
			virtual ~ITenMilManUIApp(){}
	};
}

#endif /*ITENMILMANUIAPP_H_*/
