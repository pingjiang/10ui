#include "Map_TestApp.h"
#include <TenMilManUI/TenUI_Globals.h>


#include "TenMilManUI/UI/Controls/Button/States/DownState.h"
#include "TenMilManUI/UI/Controls/Button/States/HoverState.h"

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Controls/Button/Button.h>
#include <TenMilManUI/UI/Containers/Canvas/Canvas.h>

#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include "UserInputs/TableInput_NewArch.h"

#include <tr1/memory>

using std::tr1::dynamic_pointer_cast;

namespace TenUI {

	void Map_TestApp::initInput(){
		getTenUIInputManager()->registerInput(
			shared_ptr<SDLMouseInput>(new SDLMouseInput())
		);
		getTenUIInputManager()->registerInput(
			shared_ptr<TableInput_NewArch>(new TableInput_NewArch("pitfall.vrac.iastate.edu",50002,50003))
		);
	}
	
	void Map_TestApp::styleUnit(bool isRed, const shared_ptr<DraggableButton>& unit, const string& unitIcon){
		unit->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/"+unitIcon));
		unit->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		if(!isRed){
			unit->setStateStyleValue(ButtonStates::HoverState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.25));
			unit->setStateStyleValue(ButtonStates::DownState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.75));
		}
	}

	void Map_TestApp::init() throw(int){
		
		shared_ptr<DraggableButton> container = shared_ptr<DraggableButton> (new DraggableButton(-1512,-1512, 2048,2048));
		container = shared_ptr<DraggableButton> (new DraggableButton(-100,-100, 2557,2576));

		shared_ptr<DraggableButton> newButton = shared_ptr<DraggableButton> (new DraggableButton(0,0, 60,60));
		shared_ptr<DraggableButton> newButton2 = shared_ptr<DraggableButton> (new DraggableButton(-100,-50, 60,60));
		shared_ptr<DraggableButton> newButton3 = shared_ptr<DraggableButton> (new DraggableButton(-75,-10, 60,60));
		shared_ptr<DraggableButton> newButton4 = shared_ptr<DraggableButton> (new DraggableButton(-200,-100, 60,60));
		shared_ptr<DraggableButton> newButton5 = shared_ptr<DraggableButton> (new DraggableButton(-200,-100, 60,60));
		shared_ptr<DraggableButton> newButton6 = shared_ptr<DraggableButton> (new DraggableButton(-200,-100, 60,60));
		shared_ptr<DraggableButton> newButton7 = shared_ptr<DraggableButton> (new DraggableButton(-200,-100, 60,60));
		shared_ptr<DraggableButton> newButton8 = shared_ptr<DraggableButton> (new DraggableButton(-200,-100, 60,60));

		shared_ptr<DraggableButton> newButtonb = shared_ptr<DraggableButton> (new DraggableButton(-350,10, 60,60));
		shared_ptr<DraggableButton> newButtonb2 = shared_ptr<DraggableButton> (new DraggableButton(-300,-50, 60,60));
		shared_ptr<DraggableButton> newButtonb3 = shared_ptr<DraggableButton> (new DraggableButton(-575,-10, 60,60));
		shared_ptr<DraggableButton> newButtonb4 = shared_ptr<DraggableButton> (new DraggableButton(-400,-100, 60,60));
		shared_ptr<DraggableButton> newButtonb5 = shared_ptr<DraggableButton> (new DraggableButton(-400,-100, 60,60));
		shared_ptr<DraggableButton> newButtonb6 = shared_ptr<DraggableButton> (new DraggableButton(-400,-100, 60,60));
		shared_ptr<DraggableButton> newButtonb7 = shared_ptr<DraggableButton> (new DraggableButton(-400,-100, 60,60));
		shared_ptr<DraggableButton> newButtonb8 = shared_ptr<DraggableButton> (new DraggableButton(-400,-100, 60,60));

		container->addChild(newButton);
		container->addChild(newButton2);
		container->addChild(newButton3);
		container->addChild(newButton4);
		container->addChild(newButton5);
		container->addChild(newButton6);
		container->addChild(newButton7);
		container->addChild(newButton8);
				
		container->addChild(newButtonb);
		container->addChild(newButtonb2);
		container->addChild(newButtonb3);
		container->addChild(newButtonb4);
		container->addChild(newButtonb5);
		container->addChild(newButtonb6);
		container->addChild(newButtonb7);
		container->addChild(newButtonb8);
		
		getTenUI()->addUIComponent( 
				container
    	);

		/*newButton->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/bomber_red.png"));
		newButton->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
						
		newButton2->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/bomber_red.png"));
		newButton2->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));

		newButton3->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/bomber_red.png"));
		newButton3->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		
		newButton4->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/bomber_red.png"));
		newButton4->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
*/

		styleUnit(true, newButton, "sam_red.bmp");
		styleUnit(true, newButton2, "bomber_red.png");
		styleUnit(true, newButton3, "fighter_red.png");
		styleUnit(true, newButton4, "fighter_red.png");
		styleUnit(true, newButton5, "fighter_red.png");
		styleUnit(true, newButton6, "sam_red.bmp");
		styleUnit(true, newButton7, "ground_red.bmp");
		styleUnit(true, newButton8, "ground_red.bmp");
		
		styleUnit(false, newButtonb, "sam_blue.bmp");
		styleUnit(false, newButtonb2, "bomber_blue.png");
		styleUnit(false, newButtonb3, "fighter_blue.png");
		styleUnit(false, newButtonb4, "fighter_blue.png");
		styleUnit(false, newButtonb5, "fighter_blue.png");
		styleUnit(false, newButtonb6, "sam_blue.bmp");
		styleUnit(false, newButtonb7, "ground_blue.bmp");
		styleUnit(false, newButtonb8, "ground_blue.bmp");
		
		/*newButtonb->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/sam_blue.bmp"));
		newButtonb->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		newButtonb->setStateStyleValue(ButtonStates::HoverState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.25));
		newButtonb->setStateStyleValue(ButtonStates::DownState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.75));

		
		newButtonb2->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/bomber_blue.png"));
		newButtonb2->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		newButtonb2->setStateStyleValue(ButtonStates::HoverState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.25));
		newButtonb2->setStateStyleValue(ButtonStates::DownState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.75));


		newButtonb3->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/fighter_blue.png"));
		newButtonb3->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		newButtonb3->setStateStyleValue(ButtonStates::HoverState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.25));
		newButtonb3->setStateStyleValue(ButtonStates::DownState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.75));

		newButtonb4->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/military_icons/resolved/bomber_blue.png"));
		newButtonb4->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		newButtonb4->setStateStyleValue(ButtonStates::HoverState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.25));
		newButtonb4->setStateStyleValue(ButtonStates::DownState::STATE_NAME,Button::BORDER_COLORS_STYLE,ColorHex(0.0,1.0,0.0,.75));
		 */
		
		container->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, string("resources/military/terrain_bg.jpg"));
		container->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		container->setAllStateStyleValue(Button::BORDER_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		
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
