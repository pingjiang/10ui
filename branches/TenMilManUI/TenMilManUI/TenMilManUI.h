#ifndef TENMILMANUI_H_
#define TENMILMANUI_H_

// includes
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <SDL.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tr1/memory>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>
#include <TenMilManUI/ITenMilManUIApp.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UI/Core/DisplayObject.h>
#include <TenMilManUI/UI/Core/DisplayObjectContainer.h>
#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UserInputs/UserInput.h>
#include <TenMilManUI/UI/Managers/InputManager.h>

#define IMPLEMENT_TENUI_APP( tenuiApp ) int main(void) {																			\
											TenUI::ITenMilManUIApp* app = (TenUI::ITenMilManUIApp*) new TenUI::tenuiApp;			\
											TenUI::TenMilManUI* tui = TenUI::TenMilManUI::createInstance(app);						\
											tui->run();																				\
											return 0;																				\
									  }
using namespace std;
using std::tr1::shared_ptr;

namespace TenUI {

	class ITenMilManUIApp;
	
	class TenMilManUI {
		
		// Private Variables
		private:
		    static TenMilManUI* inst;
		    IGraphics* graphics;
		    
		    map<unsigned long , shared_ptr<DisplayObject> > rootObjs;
		    map<unsigned long , shared_ptr<UIComponent> > allUIComps;
		    ITenMilManUIApp *app;
						
			// Indicates whether UI should continue running
			// Made for Multi-Threading
		    pthread_mutex_t runningMutex;
			bool running;
			
			// getUIComponentsAt
			bool runSelectionRendering; 
			
		// Private Methods
		private:
			TenMilManUI(ITenMilManUIApp *) throw(int);						
			virtual ~TenMilManUI();
						
			void update(); 
			void draw();
			bool isRunning();	
			
			void addUIComponent_Recursive(const shared_ptr<UIComponent>& uicomp);

		// Public Methods
		public:
			static TenMilManUI* createInstance(ITenMilManUIApp *) throw(int);
			static TenMilManUI* instance();			
			
			void run() throw(int);
			void quit() throw(int);

			IGraphics* getGraphics(){ return graphics; }
			GraphicsOptions& getGraphicsOptions() const { return graphics->getGraphicsOptions(); }			
			shared_ptr<UIComponent> getUIComponentsAt(int x, int y);
			
			void 						addUIComponent(const shared_ptr<UIComponent>& uicomp);
			shared_ptr<UIComponent> 	getUIComponent(unsigned long uicompid);
	};

}

#endif /*TENMILMANUI_H_*/
