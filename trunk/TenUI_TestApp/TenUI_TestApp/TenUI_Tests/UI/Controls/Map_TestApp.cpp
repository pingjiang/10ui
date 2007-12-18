#include "Map_TestApp.h"
#include <TenMilManUI/TenUI_Globals.h>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Controls/Button/Button.h>
#include <TenMilManUI/UI/Controls/DraggableButton/DraggableButton.h>
#include <TenMilManUI/UI/Containers/Canvas/Canvas.h>

#include <TenMilManUI/UserInputs/SDLMouseInput.h>

//#include "UserInputs/TableInput_NewArch.h"

#include <tr1/memory>

using std::tr1::dynamic_pointer_cast;

namespace TenUI {

	void Map_TestApp::initInput(){
		getTenUIInputManager()->registerInput(
			shared_ptr<SDLMouseInput>(new SDLMouseInput())
		);
		/*getTenUIInputManager()->registerInput(
			shared_ptr<TableInput_NewArch>(new TableInput_NewArch("pitfall.vrac.iastate.edu",50002,50003))
		);*/
	}

	void Map_TestApp::init() throw(int){
		//prevObjID = 0;
		
		/*int strokeSize = 3;
		int buttonSize = 128;
		for(unsigned int i = 0; i < 1024; i+=buttonSize){
            for(unsigned int j = 0; j < 768; j+=buttonSize){
    			shared_ptr<Button> newButton(
    					new Button(i+strokeSize, j+strokeSize, buttonSize-strokeSize, buttonSize-strokeSize)
    			);
    			newButton->setOpacity((float)j/768.0);
            	getTenUI()->addUIComponent( 
            			newButton
            	);
            }
        }
		

		shared_ptr<Canvas> newCanvas(new Canvas(0,0,0,0));
		newCanvas->setOpacity(.25);
    	getTenUI()->addUIComponent( newCanvas );
		newCanvas->setStyleValue(Canvas::BACKGROUND_IMAGE, string("resources/images/myScreenShot.png"));*/

		shared_ptr<DraggableButton> newButton(
				new DraggableButton(300,300, 128,128)
		);
		
		newButton = shared_ptr<DraggableButton> (new DraggableButton(-100,-100, 2557,2576));
		getTenUI()->addUIComponent( 
    			newButton
    	);
		newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/images/airphotousa_twintowers.jpg"));
		
	}
	
	void Map_TestApp::update_frame() throw(APPEXCEPTIONS) {		
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
