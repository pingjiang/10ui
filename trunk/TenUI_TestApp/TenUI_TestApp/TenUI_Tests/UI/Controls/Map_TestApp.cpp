#include "Map_TestApp.h"
#include <TenMilManUI/TenUI_Globals.h>

// UIComponent
#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Controls/Button/Button.h>

// Button States
#include "TenMilManUI/UI/Controls/Button/States/DownState.h"
#include "TenMilManUI/UI/Controls/Button/States/HoverState.h"


// UserInputs
#include <TenMilManUI/UserInputs/SDLMouseInput.h>
//#include <TenUI_TestApp/UserInputs/TableInput_NewArch.h>

#include <tr1/memory>

using std::tr1::dynamic_pointer_cast;

namespace TenUI {

	IGraphics* Map_TestApp::initGraphics() { 
		OpenGL_Graphics* graphics = OpenGL_Graphics::instance();
		graphics->init(new GraphicsOptions(	"UI Controls Test App",
											1024, 768, 32, 
									 		IGraphicsEnums::FULLSCREEN, 
									 		string(""))
		);
		return graphics;
	}

	void Map_TestApp::initUserInputs(){
		getTenUIInputManager()->registerInput(
			shared_ptr<SDLMouseInput>(new SDLMouseInput())
		);
		/*getTenUIInputManager()->registerInput(
			shared_ptr<TableInput_NewArch>(new TableInput_NewArch("pitfall.vrac.iastate.edu",50002,50003))
		);*/
	}
	
	shared_ptr<UIComponent> Map_TestApp::createMap(const string& mapImage, int x, int y, int w, int h){
		// Create Map Container
		shared_ptr<DraggableButton> map = DraggableButton::create();
		map->setXY(x,y);
		map->setWH(w,h);
		
		map->setAllStateStyleValue(DraggableButton::BACKGROUND_IMAGE, mapImage);
		map->setAllStateStyleValue(Button::FILL_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		map->setAllStateStyleValue(Button::BORDER_COLORS_STYLE, ColorHex(0.0,0.0,0.0,0.0));
		
		return dynamic_pointer_cast<UIComponent>(map);
	}
	
	shared_ptr<UIComponent> Map_TestApp::createUnit(bool isRed, const string& unitIcon, int x, int y){
		// Create unit as a DraggableButton
		shared_ptr<DraggableButton> unit = DraggableButton::create();
		
		// Set location and size
		unit->setXY(x,y);
		unit->setWH(60,60);
		
		// Set Unit Image
		unit->setAllStateStyleValue(
				DraggableButton::BACKGROUND_IMAGE, 	
				string("resources/military/military_icons/resolved/"+unitIcon)
		);
		
		// Remove Fill Color
		unit->setAllStateStyleValue(
				Button::FILL_COLORS_STYLE, 			
				ColorHex(0.0,0.0,0.0,0.0)
		);
		
		// Set Styling (Border color)
			// Set HoverState Borders Style
			unit->setStateStyleValue(
					ButtonStates::HoverState::STATE_NAME,
					Button::BORDER_COLORS_STYLE,
					(isRed) ? ColorHex( 1.0, 0.0, 0.0, .25)
							: ColorHex( 0.0, 1.0, 0.0, .25)
					
			);
			
			// Set DownState Borders Style
			unit->setStateStyleValue(
					ButtonStates::DownState::STATE_NAME,
					Button::BORDER_COLORS_STYLE,
					(isRed) ? ColorHex( 1.0, 0.0, 0.0, .75)
							: ColorHex( 0.0, 1.0, 0.0, .75)
			);
		
		return dynamic_pointer_cast<UIComponent>(unit);
	}

	void Map_TestApp::init(){		
		
		// Create Map Container
		mapui = createMap(string("resources/military/terrain_bg.jpg"), -1512,-1512, 2048,2048);
		
			// Add Units
			mapui->addChild( createUnit(true, "sam_red.bmp", 		0,		0	) );
			mapui->addChild( createUnit(true, "bomber_red.png", 	-100, 	-50	) );
			mapui->addChild( createUnit(true, "fighter_red.png",	-75, 	-10	) );
			mapui->addChild( createUnit(true, "fighter_red.png",	-200, 	-100) );
			mapui->addChild( createUnit(true, "fighter_red.png",	-200, 	-100) );
			mapui->addChild( createUnit(true, "sam_red.bmp", 		-200, 	-100) );
			mapui->addChild( createUnit(true, "ground_red.bmp", 	-200, 	-100) );
			mapui->addChild( createUnit(true, "ground_red.bmp", 	-200, 	-100) );
			
			mapui->addChild( createUnit(false, "sam_blue.bmp", 		-350, 	10	) );
			mapui->addChild( createUnit(false, "bomber_blue.png",	-300, 	-50	) );
			mapui->addChild( createUnit(false, "fighter_blue.png",	-575,	-10	) );
			mapui->addChild( createUnit(false, "fighter_blue.png",	-400, 	-100) );
			mapui->addChild( createUnit(false, "fighter_blue.png",	-400, 	-100) );
			mapui->addChild( createUnit(false, "sam_blue.bmp",		-400, 	-100) );
			mapui->addChild( createUnit(false, "ground_blue.bmp",	-400, 	-100) );
			mapui->addChild( createUnit(false, "ground_blue.bmp",	-400, 	-100) );
		
		getTenUI()->addUIComponent( mapui );
		
	}
	
	void Map_TestApp::update_frame(){}
}
