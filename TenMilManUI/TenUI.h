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
	 
	class TenUI {
		
		// Private Variables
		private:
		    static TenUI* inst;
		    IGraphics* graphics;
		    
		    vector< shared_ptr<DisplayObject> > rootObjs;
		    map<unsigned long , shared_ptr<UIComponent> > allUIComps;
		    ITenUIApp *app;
						
			// Indicates whether UI should continue running
			// Made for Multi-Threading
		    pthread_mutex_t runningMutex;
			bool running;
			
			// getUIComponentsAt
			bool runSelectionRendering; 
			
		// Private Methods
		private:
			TenUI(ITenUIApp *) throw(int);						
			virtual ~TenUI();
						
			void update(); 
			void draw();
			bool isRunning();	
			
			void addUIComponent_Recursive(const shared_ptr<UIComponent>& uicomp);

		// Public Methods
		public:
			static TenUI* createInstance(ITenUIApp *) throw(int);
			static TenUI* instance();			
			
			void run() throw(int);
			void quit() throw(int);

			IGraphics* getGraphics(){ return graphics; }
			GraphicsOptions& getGraphicsOptions() const { return graphics->getGraphicsOptions(); }			
			
			void 						addUIComponent(const shared_ptr<UIComponent>& uicomp);
			shared_ptr<UIComponent> 	getUIComponent(unsigned long uicompid);
			shared_ptr<UIComponent> 	getUIComponentsAt(int x, int y);

			void 						bringUIComponentFront(const shared_ptr<UIComponent>& uicomp);
			void 						bringUIComponentFront(unsigned long uicompid);
						
	};

}

#endif /*TENUI_H_*/
