#include "UIControls_TestApp.h"
#include <TenMilManUI/TenUI_Globals.h>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Controls/Button/Button.h>
#include <TenMilManUI/UI/Controls/DraggableButton/DraggableButton.h>

#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include "UserInputs/TableInput_NewArch.h"

#include <tr1/memory>

using std::tr1::dynamic_pointer_cast;

namespace TenUI {

	void UIControls_TestApp::initInput(){
		getTenUIInputManager()->registerInput(
			shared_ptr<SDLMouseInput>(new SDLMouseInput())
		);
		getTenUIInputManager()->registerInput(
			shared_ptr<TableInput_NewArch>(new TableInput_NewArch("pitfall.vrac.iastate.edu",50002,50003))
		);
	}

	void UIControls_TestApp::init() throw(int){

		shared_ptr<DraggableButton> newButton(
				new DraggableButton(300,300, 128,128)
		);
		
		newButton = shared_ptr<DraggableButton> (new DraggableButton(100,250, 256,192));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/architectural-wonders-1.jpg"));
		newButton = shared_ptr<DraggableButton> (new DraggableButton(200,600, 256,192));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/architectural-wonders-10.jpg"));
		newButton = shared_ptr<DraggableButton> (new DraggableButton(400,300, 256,192));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/architectural-wonders-16.jpg"));
		newButton = shared_ptr<DraggableButton> (new DraggableButton(600,100, 256,192));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/architectural-wonders-2.jpg"));
		newButton = shared_ptr<DraggableButton> (new DraggableButton(300,500, 256,192));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/architectural-wonders-8.jpg"));
		
		

		newButton = shared_ptr<DraggableButton> (new DraggableButton(300,500, 300,300));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/nsfe.tif"));


		newButton = shared_ptr<DraggableButton> (new DraggableButton(300,500, 300,300));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/vrac_logo_medium_001.sized.jpg"));

		
		newButton = shared_ptr<DraggableButton> (new DraggableButton(400,190, 400,190));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/CNN.jpg"));
	}
	
	void UIControls_TestApp::update_frame() throw(APPEXCEPTIONS) {		
		/*shared_ptr< UIComponent > uicomp = getTenUI()->getUIComponentsAt(getTenUI()->getUserInput()->getX(),getTenUI()->getUserInput()->getY());
		if( uicomp != NULL ){
			if(prevObjID != uicomp->getObjectID()){
				prevObjID = uicomp->getObjectID();
				cout << "hovered UIComponent: id=" << prevObjID << endl;
			}
		}else{
			prevObjID = 0;
		}*/
	}
}
