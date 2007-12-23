#ifndef ITENUIAPP_H_
#define ITENUIAPP_H_

#include <string>

#include <TenMilManUI/TenUI.h>
#include <TenMilManUI/TenUI_Enums.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>

using std::string;


namespace TenUI {

	class TenUI;

	enum APPEXCEPTIONS { APPEXCEPTION_TENMILMANUIAPP_INIT_FAILED };

	class ITenUIApp {
		private:		
		protected:
		public:
			virtual ~ITenUIApp(){};
			
			virtual void initInput() = 0;
			virtual void init() = 0;
			virtual void update_preframe() = 0;
			virtual void update_frame() = 0;
			virtual void deinit() = 0;
			
			virtual GraphicsOptions* getGraphicsOptions() = 0;
			virtual IGraphics* 		 getGraphics() = 0;
	};
}

#endif /*ITENUIAPP_H_*/
