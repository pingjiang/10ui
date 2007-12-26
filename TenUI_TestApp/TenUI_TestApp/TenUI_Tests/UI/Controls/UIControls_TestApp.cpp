#include "UIControls_TestApp.h"
#include <TenMilManUI/TenUI_Globals.h>

// UIComponent
#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Controls/Button/Button.h>
#include <TenMilManUI/UI/Controls/DraggableButton/DraggableButton.h>

// UserInputs
#include <TenMilManUI/UserInputs/SDLMouseInput.h>
//#include <TenUI_TestApp/UserInputs/TableInput_NewArch.h>

#include <tr1/memory>
using std::tr1::dynamic_pointer_cast;

namespace TenUI {

	IGraphics* UIControls_TestApp::initGraphics() { 
		OpenGL_Graphics* graphics = OpenGL_Graphics::instance();
		graphics->init(new GraphicsOptions(	"UI Controls Test App",
											1024, 768, 32, 
									 		IGraphicsEnums::WINDOWED, 
									 		string(""))
		);
		return graphics;
	}


	void UIControls_TestApp::initUserInputs(){
		getTenUIInputManager()->registerInput(
			shared_ptr<SDLMouseInput>(new SDLMouseInput())
		);
		/*getTenUIInputManager()->registerInput(
			shared_ptr<TableInput_NewArch>(new TableInput_NewArch("pitfall.vrac.iastate.edu",50002,50003))
		);*/
	}
	

	shared_ptr<UIComponent>	UIControls_TestApp::createPicture(const string& picPath, int x, int y, int w, int h){
		shared_ptr<DraggableButton> newButton = DraggableButton::create();
		newButton->setXY(x,y);
		newButton->setWH(w,h);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, picPath);
		return dynamic_pointer_cast<UIComponent>(newButton);
	}

	void UIControls_TestApp::init(){

		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/architectural-wonders-1.jpg",
						100, 250, 
						256, 192)
    	);
				
		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/architectural-wonders-10.jpg",
						200, 600, 
						256, 192)
    	);
		
		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/architectural-wonders-16.jpg",
						400, 300, 
						256, 192)
    	);
		
		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/architectural-wonders-2.jpg",
						600, 100, 
						256, 192)
    	);
		
		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/architectural-wonders-8.jpg",
						300,500, 
						256, 192)
    	);
		
		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/nsfe.tif",
						300, 500, 
						300, 300)
    	);

		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/vrac_logo_medium_001.sized.jpg",
						300, 500, 
						300, 300)
    	);
		
		getTenUI()->addUIComponent( 
				createPicture(
						"resources/images/CNN.jpg",
						400, 190, 
						400, 190)
    	);
	}
}
