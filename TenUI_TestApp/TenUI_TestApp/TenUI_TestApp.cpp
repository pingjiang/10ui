#include "TenUI_TestApp.h"
#include <TenMilManUI/TenUI_Globals.h>
#include <TenMilManUI/UI/Controls/Button.h>

// TenUI Application Entry Point
IMPLEMENT_TENUI_APP(TenUI_TestApp)

namespace TenUI {

	void TenUI_TestApp::initButtonTest(){
		Button* b = new Button(0, 0);
		getTenUI()->addDisplayObject(b);
	}

	void TenUI_TestApp::init() throw(int) {		
		initButtonTest();
	}
	
}
