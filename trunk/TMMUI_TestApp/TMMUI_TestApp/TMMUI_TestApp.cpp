#include "TMMUI_TestApp.h"


	int main(void){		
		TenMilManUI_APP::ITenMilManUIApp* app = (TenMilManUI_APP::ITenMilManUIApp*) (new TenMilManUI_APP::TMMUI_TestApp());
		TenMilManUI_CORE::TenMilManUI* tui = TenMilManUI_CORE::TenMilManUI::createInstance(app);		
		tui->run();
	}

