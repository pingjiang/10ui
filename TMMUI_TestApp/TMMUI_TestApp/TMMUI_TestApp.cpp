#include "TMMUI_TestApp.h"

namespace TenMilManUI_APP {
		
	void TMMUI_TestApp::initRectangleTest(){			
		Rectangle *tmpRect;
		for(unsigned int i = 0; i < 1280; i+=64){
			for(unsigned int j = 0; j < 1024; j+=64){
				tmpRect = new Rectangle(NULL, i, j, 64, 64, 			// x,y,w,h
											  (i)/1280.0, (j)/1024.0, ((i+j))/1302.0, 	// fill color
											  ((i+j))/1302.0, (i)/1280.0, (j)/1024.0, 	// stroke color
											  (j/(1024.0-64))*10.0);	
				TenMilManUI::instance()->addDisplayObject(tmpRect);
			}
		}
	}
	
	void TMMUI_TestApp::initLineTest(){		
		Line *tmpLine;
		for(unsigned int i = 0; i < 1280; i+=64){
			for(unsigned int j = 0; j < 1024; j+=64){			
				tmpLine = new Line(NULL, i+((float)i/(1280.0-64))*64.0, j+((float)j/(1024.0-64))*64.0, (i+64)-((float)i/(1280.0-64))*64.0, (j+64)-((float)j/(1024.0-64))*64.0,	//x,y,x2,y2
										(i)/1280.0, ((i+j))/1302.0, (j)/1024.0, 	// stroke color
										((double)i/(1280.0-64.0))*4+1.0);			//stroke size										 
				TenMilManUI::instance()->addDisplayObject(tmpLine);
			}
		}
	}
	
	void TMMUI_TestApp::initRasterTest(){
		Rasterable *tmpRaster = new Rasterable(NULL, 1024,640);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/bomber_blue.png");
		TenUI->addDisplayObject(tmpRaster);

		tmpRaster = new Rasterable(NULL, 64,64);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/barney.jpg");	
		TenUI->addDisplayObject(tmpRaster);
		
		tmpRaster = new Rasterable(NULL, 704,64);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/keepon_motion.jpg");	
		TenUI->addDisplayObject(tmpRaster);
	}
	
	void TMMUI_TestApp::initTextTest(){
		try{
			FontMgr.loadFont("TestResources/FontTest/CALIBRI.TTF","Calibra");
		}catch(int e){
			switch(e){
			case FontManager_FT2::LOAD_FONT_EXCEPTION:
				cout << "Load Font Exception" << endl;
			case FontManager_FT2::FONTKEY_ALREADY_EXISTS:
				cout << "FontKey already exists" << endl;
			}
		}
		

		Rectangle *tmpRect = new Rectangle(NULL, 64, 768, 576, 64, 			// x,y,w,h
											  0,0,0, 	// fill color
											  0,0,0, 	// stroke color
											  0);	
		TenUI->addDisplayObject(tmpRect);
		
		Text *text = new Text(NULL, 64, 768);
		text->setFont("Calibra");
		text->setFontSize(16);
		text->setText("I find out what the world needs, then I proceed to invent");
		text->setColor("#FFF");
		TenUI->addDisplayObject((DisplayObject*)text);		
	}
	

	void TMMUI_TestApp::init() throw(int) {	
		initRectangleTest();
		initLineTest();
		initTextTest();
		initRasterTest();						
	}

}

	int main(void){		
		TenMilManUI_APP::ITenMilManUIApp* app = (TenMilManUI_APP::ITenMilManUIApp*) (new TenMilManUI_APP::TMMUI_TestApp());
		TenMilManUI_CORE::TenMilManUI* tui = TenMilManUI_CORE::TenMilManUI::createInstance(app);		
		tui->run();
	}

