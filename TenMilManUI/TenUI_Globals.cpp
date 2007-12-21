#include "TenUI_Globals.h"

namespace TenUI{
	TenUI* getTenUI(){
		return TenUI::instance();
	}
	IGraphics* getTenUIGraphics(){
		return TenUI::instance()->getGraphics();
	}
	shared_ptr<InputManager> getTenUIInputManager() { 
		return InputManager::instance(); 
	}
}
