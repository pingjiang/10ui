#ifndef ITENMILMANUIAPP_H_
#define ITENMILMANUIAPP_H_

namespace TenMilManUI {

	enum APPEXCEPTIONS { APPEXCEPTION_TENMILMANUIAPP_INIT_FAILED };

	class ITenMilManUIApp {
		public:
			ITenMilManUIApp();
			
			virtual void init() throw(int) = 0;
			virtual void update_preframe() throw(int) = 0;
			virtual void update_frame() throw(int) = 0;
			virtual void deinit() throw(int) = 0;
			
			virtual ~ITenMilManUIApp(){}
	};
}

#endif /*ITENMILMANUIAPP_H_*/
