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

	/**
	 * Subclassed by TenUI Applications
	 * This interface is the construct of a TenUI application.  It declares the basics that the TenUI Application must supply.
	 * TenUI uses this interface to 
	 * 	- setup the display 
	 * 	- setup the input 
	 * 	- initialize the application
	 * 	- notify the application of:
	 * 		- frame rendering is about to occur (preframe)
	 * 		- frame rendering is occurring (frame)
	 * 	- deinitialize the application when execution has been halted. 
	 */
	class ITenUIApp {
		public:
			virtual ~ITenUIApp(){};

			/** @name Initialization Methods  
			 *  Callback methods called before and during frame rendering. 
			 */
			//@{
			
			/**
			 * Applications should initialize their IGraphics object here.
			 * TenUI will use IGraphics object for rendering.
			 *  
			 * @return pointer to IGraphics object
			 */
			virtual IGraphics* 	initGraphics() = 0;
			
			/**
			 * Applications should initialize and register UserInput objects to UserInputManager
			 * 
			 * @see UserInputManager
			 */ 
			virtual void 		initUserInputs() = 0;
			
			/**
			 * Applications should place any initialization code here.
			 * Code that initializes and registers UI Controls and Containers can be placed in this method.
			 */   
			virtual void 		init() = 0;
			virtual void 		deinit() = 0;
			//@}

			/** @name Application Loop Methods 
			 *  Callback methods called before and during frame rendering. 
			 */
			//@{
			/**
			 * Callback method called before frame rendering.
			 */
			virtual void 		update_preframe() = 0;

			/**
			 * Callback method called during frame rendering.
			 * This method will be ran in parallel to frame rendering. 
			 * Processing that doesn't not effect rendering should reside here.
			 */
			virtual void 		update_frame() = 0;
			//@}
	};
}

#endif /*ITENUIAPP_H_*/
