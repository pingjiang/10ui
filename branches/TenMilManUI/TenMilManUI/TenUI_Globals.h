#ifndef TENUI_GLOBALS_H_
#define TENUI_GLOBALS_H_

#include "TenMilManUI.h"

namespace TenUI{
	TenMilManUI* getTenUI();
	IGraphics* getTenUIGraphics();
	shared_ptr<TenUI::InputManager> getTenUIInputManager();
}

#endif /*TENUI_GLOBALS_H_*/
