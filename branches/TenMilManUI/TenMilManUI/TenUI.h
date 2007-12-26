#ifndef TENUI_H_
#define TENUI_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tr1/memory>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>
#include <TenMilManUI/ITenUIApp.h>
#include <TenMilManUI/UI/Core/DisplayObject.h>
#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UserInputs/UserInput.h>
#include <TenMilManUI/UI/Managers/InputManager.h>

#define IMPLEMENT_TENUI_APP( tenuiApp ) int main(void) {																			\
											TenUI::ITenUIApp* app = (TenUI::ITenUIApp*) new TenUI::tenuiApp;							\
											TenUI::TenUI* tui = TenUI::TenUI::createInstance(app);									\
											tui->run();																				\
											return 0;																				\
									  	}
using namespace std;
using std::tr1::shared_ptr;

namespace TenUI {

	class ITenUIApp;
	
	/**
	 * Singleton class that manages TenUI Input, Graphics, UIComponents, and Application
	 */
	class TenUI {
		
		/** @name Singleton Implementation Methods
		 *  Methods for adding, removing, and querying UIComponents. 
		 */
		//@{
		private:
		    static TenUI* inst;
		public:
			/**
			 * Creates a new instance of TenUI given a ITenUIApp.
			 * Should only be used by the IMPLEMENT_TENUI_APP macros
			 */
			static TenUI* createInstance(ITenUIApp *) throw(int);
			
			/**
			 * Returns a pointer to the TenUI object.
			 */
			static TenUI* instance();

		// Constructor Destructor
		private:
			TenUI(ITenUIApp *) throw(int);						
			virtual ~TenUI();
		//@}
		
		/** @name Graphics Methods
		 *  Getters for the current IGraphics and GraphicsOptions objects.
		 */
		//@{
		private: 	
		    IGraphics* graphics;
		public:
			
			/**
			 * Returns a pointer to the IGraphics.
			 */
			IGraphics* getGraphics(){ return graphics; }
			
			/**
			 * Returns the GraphicsOptions, currently being used describe the display.   
			 */
			GraphicsOptions& getGraphicsOptions() const { return graphics->getGraphicsOptions(); }			
		//@}

		/** @name UIComponent Management Methods
		 *  Methods for adding, removing, and querying UIComponents. 
		 */
		//@{
		private:
		    vector< shared_ptr<DisplayObject> > rootObjs;
		    map<unsigned long , shared_ptr<UIComponent> > allUIComps;
		public:
			/**
			 * Adds a UIComponent at the root level.
			 * 
			 * @param uicomp 	New UIComponent to be added.
			 */
			void 						addUIComponent(const shared_ptr<UIComponent>& uicomp);
			/**
			 * Removes UIComponent from TenUI.  Doesn't have to be at the root level.
			 * 
			 * @param uicompid	DisplayObject ID of the UIComponent.
			 */  
			void 						removeUIComponent(DisplayObjectIDType uicompid){}

			/**
			 * Gets a pointer to a UIComponent given a DisplayObject ID
			 * 
			 * @param uicompid	Display Object ID of the UIComponent.
			 */
			shared_ptr<UIComponent> 	getUIComponent(DisplayObjectIDType uicompid);

			/**
			 * Gets a pointer to the top-most UIComponent at a given screen coordinate.
			 * "top-most" describes a UIComponent that rendered later then others, and thus rendered ontop of possibly overlapping UIComponents.  
			 * 
			 * @param x 		X screen cordinate
			 * @param y 		Y screen coordinate
			 */
			shared_ptr<UIComponent> 	getUIComponentsAt(int x, int y);
			
		private:
			void addUIComponent_Recursive(const shared_ptr<UIComponent>& uicomp);
		//@}			
		
		/** @name Start Stop Execution Methods
		 *  Methods for starting and stopping TenUI 
		 */
		//@{
		public:
			/** 
			 * Kicks off execution of the registered TenUI application
			 * This is a blocking call.
			 */
			void run();
			/**
			 * Requests a halt of execution.
			 * Execution will stop the next cycle that processes a quit has been requested.
			 * TenUI Applications should call this method to exit.
			 */
			void quit();
			
		private:
			void update(); 
			void draw();
			
			bool isRunning();	
			bool running;
			
			// TODO moved to graphics
			bool runSelectionRendering; 
		//@}

			
		// TenUI App
		private:
		    ITenUIApp *app;
			
						
		// TODO Localize to UIComponents.  UIComponent should offer this function to allow reording of children
		public:		
			void 						bringUIComponentFront(const shared_ptr<UIComponent>& uicomp);
			void 						bringUIComponentFront(unsigned long uicompid);
						
	};

}

#endif /*TENUI_H_*/
