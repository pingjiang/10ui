#include "TenUI_Globals.h"

namespace TenUI{
	TenUI* getTenUI(){
		return TenUI::instance();
	}
	IGraphics* getTenUIGraphics(){
		return TenUI::instance()->getGraphics();
	}
	sp<InputManager> getTenUIInputManager() { 
		return InputManager::instance(); 
	}
}
