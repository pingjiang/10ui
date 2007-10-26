#include "TenUI_Globals.h"

namespace TenUI{
	TenMilManUI* getTenUI(){
		return TenMilManUI::instance();
	}
	IGraphics* getTenUIGraphics(){
		return TenMilManUI::instance()->getGraphics();
	}
}
