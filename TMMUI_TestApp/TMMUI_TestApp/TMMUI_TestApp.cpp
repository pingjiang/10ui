#include "TMMUI_TestApp.h"


// TenUI Application Entry Point
IMPLEMENT_TENUI_APP(TMMUI_TestApp)

namespace TenUI {
		
	void TMMUI_TestApp::initRectangleTest(){			
		Rectangle *tmpRect2;
		InteractiveRectangle *tmpRect;
		for(unsigned int i = 0; i < 1280; i+=64){
			for(unsigned int j = 0; j < 1024; j+=64){
				tmpRect2 = new Rectangle(NULL, i, j, 64, 64, 			// x,y,w,h
										(i)/1280.0, (j)/1024.0, ((i+j))/1302.0, 	// fill color
										((i+j))/1302.0, (i)/1280.0, (j)/1024.0, 	// stroke color
										(j/(1024.0-64))*10.0);	
				tmpRect = new InteractiveRectangle(NULL, i, j, 64, 64, 			// x,y,w,h
											  (i)/1280.0, (j)/1024.0, ((i+j))/1302.0, 	// fill color
											  ((i+j))/1302.0, (i)/1280.0, (j)/1024.0, 	// stroke color
											  (j/(1024.0-64))*10.0, 0,1,1, tmpRect2);	
				//TenMilManUI::instance()->addDisplayObject(tmpRect);
				TMMUI_TestApp::sltMgr->registerObj((UIComponent*)tmpRect);
				getTenUI()->addDisplayObject(tmpRect2);
				getTenUI()->addDisplayObject(tmpRect);
			}
		}
	}
	
	void TMMUI_TestApp::initInteractiveRectangleTest(){			
			InteractiveRectangle *tmpRect;
			Rectangle *tmpRect2;
			int i = 0, j = 100;
			float r = 0.5, g = 0.0, b = 0.0, sr = 1.0, sg = 1.0, sb = 1.0, sw = 2.0;
			tmpRect2 = new Rectangle(NULL, i, j, 100, 100, 			// x,y,w,h
														  r, g, b, 	// fill color
														  sr, sg, sb, 	// stroke color
														  sw);	
			tmpRect = new InteractiveRectangle(NULL, i, j, 100, 100, 			// x,y,w,h
											   r, g, b, 	// fill color
											   sr, sg, sb, 	// stroke color
											   sw,0.0,1.0,1.0, tmpRect2);
			
			//TMMUI_TestApp::sltMgr->registerObj((UIComponent*)tmpRect2);
						getTenUI()->addDisplayObject(tmpRect2);
						
			TMMUI_TestApp::sltMgr->registerObj((UIComponent*)tmpRect);
			getTenUI()->addDisplayObject(tmpRect);
						
		}
	
	void TMMUI_TestApp::initLineTest(){		
		Line *tmpLine;
		for(unsigned int i = 0; i < 1280; i+=64){
			for(unsigned int j = 0; j < 1024; j+=64){			
				tmpLine = new Line(NULL, (int)(i+((float)i/(1280.0-64))*64.0), (int)(j+((float)j/(1024.0-64))*64.0), (int)((i+64)-((float)i/(1280.0-64))*64.0), (int)((j+64)-((float)j/(1024.0-64))*64.0),	//x,y,x2,y2
										(float)((i)/1280.0), (float)((i+j)/1302.0), (float)((j)/1024.0), 	// stroke color
										(float)((double)i/(1280.0-64.0))*4+1.0);			//stroke size										 
				//TenMilManUI::instance()->addDisplayObject(tmpLine);
				getTenUI()->addDisplayObject(tmpLine);
			}
		}
	}
	
	void TMMUI_TestApp::initRasterTest(){
		/*Rasterable *tmpRaster = new Rasterable(NULL, 1024,640);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/bomber_blue.png");
		sltMgr->regis{
		{
			
		}terObj((UIComponent*)tmpRaster);
		getTenUI()->addDisplayObject(tmpRaster);*/

		Rasterable *tmpRaster = new Rasterable(NULL, 1034,640);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/bomber_red.png");
		sltMgr->registerObj((UIComponent*)tmpRaster);
		getTenUI()->addDisplayObject(tmpRaster);

		
		/*tmpRaster = new Rasterable(NULL, 64,64);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/barney.jpg");
		sltMgr->registerObj((UIComponent*)tmpRaster);
		getTenUI()->addDisplayObject(tmpRaster);
		
		tmpRaster = new Rasterable(NULL, 704,64);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/keepon_motion.jpg");
		sltMgr->registerObj((UIComponent*)tmpRaster);
		getTenUI()->addDisplayObject(tmpRaster);*/
	}
	
	void TMMUI_TestApp::initTextTest(){
		Rectangle *tmpRect = new Rectangle(NULL, 64, 768, 640, 64, 			// x,y,w,h
											  .1,0,.8, 	// fill color
											  0,0,0, 	// stroke color
											  0);	
		getTenUI()->addDisplayObject(tmpRect);
		
		Text *text = new Text(NULL, 64, 768);
		text->setFont("Calibri");
		text->setFontSize(18);
		text->setText("I find out what the world needs, then I proceed to invent");
		text->setColor("#ff8811");
		getTenUI()->addDisplayObject((DisplayObject*)text);
		
		
	}
	

	void TMMUI_TestApp::init() throw(int) {
		sltMgr = new SelectManager();
		sltMgr->init();

		//initInteractiveRectangleTest();
		initRectangleTest();
		//initLineTest();
		//initTextTest();
		//initRasterTest();						
	}
	
	void TMMUI_TestApp::update_frame() throw(APPEXCEPTIONS) {
		sltMgr->update();
	}
	
}

