#ifndef TENUI_GLOBALS_H_
#define TENUI_GLOBALS_H_

#include "TenUI.h"

namespace TenUI{
	TenUI* getTenUI();
	IGraphics* getTenUIGraphics();
	shared_ptr<InputManager> getTenUIInputManager();
}

#endif /*TENUI_GLOBALS_H_*/
