#include "TMMUI_TestApp.h"
#include <iostream>
#include <string>

// TenUI Application Entry Point
IMPLEMENT_TENUI_APP(TMMUI_TestApp)

std::string ltoa(long l){
	std::string s = "";
	char c;
	while(l / 10 > 0 || l % 10 != 0)
	{
		c = (char)(l % 10 + 48);
		s = c + s;
		l = l / 10;
	}
	
	return s;
}

namespace TenUI {
		
	void TMMUI_TestApp::initRectangleTest(){			
		/*Rectangle *tmpRect2;
		DraggableRectangle *tmpRect;
		Text *tmpText;
		
		float w = getScreenWidth(), h = getScreenHeight();
		
		for(unsigned int i = 0; i < w; i+=64){
			for(unsigned int j = 0; j < h; j+=64){
				tmpText = new Text(NULL,i,j);
				tmpRect2 = new Rectangle(NULL, i, j, 64, 64, 			// x,y,w,h
										(i+128)/w, (j+128)/h, ((i+j+256))/(w+h), 	// fill color
										((i+j))/(w+h), (i)/w, (j)/h, 	// stroke color
										4.0);	
				tmpRect = new DraggableRectangle(NULL, i, j, 64, 64, 			// x,y,w,h
						(i)/w, (j)/h, ((i+j))/(w+h), 	// fill color
						((i+j))/(w+h), (i)/w, (j)/h, 	// stroke color
						4.0,0,0,1,tmpRect2,tmpText);
				
				
				tmpText->setFont("Calibri");
				tmpText->setFontSize(12);
				tmpText->setText(ltoa(tmpRect->getObjectID()));
				tmpText->setColor("#000");
				
				getTenUI()->addDisplayObject(tmpText);
				getTenUI()->addDisplayObject(tmpRect2);
				getTenUI()->addDisplayObject(tmpRect);
			}
		}*/
	}
	
	void TMMUI_TestApp::initLotsOfRectanglesTest(){
		/*Rectangle *tmpRect2;
		SelectableRectangle *tmpRect = NULL;
		DraggableRectangle *tmpDrgRect = NULL;
		Text *tmpText;
		
		float w = getScreenWidth(), h = getScreenHeight(), r = 0,g = 0,b = 0;
		bool condition;
		for(unsigned int i = 0; i < w; i+=64){
			for(unsigned int j = 0; j < h; j+=64){
				
				condition = (((i/64)%2) != ((j/64)%2));
				
				r = (condition ? 1 : 0); //r = (i < (w/2) ? 1 : 0);
				g = .25;
				b = (condition ? 0 : 1); //b = (i < (w/2) ? 0 : 1);
				tmpRect2 = new Rectangle(NULL, i, j, 64, 64, 			// x,y,w,h
										r, g, b, 	// fill color
										((i+j))/(w+h), (i)/w, (j)/h, 	// stroke color
										4.0);
				tmpText = new Text(NULL,i,j);
				
				if(condition)
				{
					tmpRect = new SelectableRectangle(NULL, i, j, 64, 64, 			// x,y,w,h
							r, g, b, 	// fill color
							((i+j))/(w+h), (i)/w, (j)/h, 	// stroke color
							4.0,0,0,1,tmpRect2, tmpText);
				}
				else
				{
					tmpDrgRect = new DraggableRectangle(NULL, i, j, 64, 64, 			// x,y,w,h
												r, g, b, 	// fill color
												((i+j))/(w+h), (i)/w, (j)/h, 	// stroke color
												4.0,0,0,1,tmpRect2, tmpText);
				}
				
				
				tmpText->setFont("Calibri");
				tmpText->setFontSize(12);
				
				if(condition)
				tmpText->setText(ltoa(tmpRect->getObjectID()));
				else
				tmpText->setText(ltoa(tmpDrgRect->getObjectID()));
				
				tmpText->setColor("#000");
				
				getTenUI()->addDisplayObject(tmpText);
				getTenUI()->addDisplayObject(tmpRect2);
				if(condition)
				getTenUI()->addDisplayObject(tmpRect);
				else
				getTenUI()->addDisplayObject(tmpDrgRect);
			}
		}*/
	}
	
	void TMMUI_TestApp::initChildrenTest(){
		Rectangle *rect = new Rectangle(NULL, 100, 100, 128, 128, .2, .2, .2, 1, 1, 1, 4.0);
		Text *caption = new Text(NULL,100,100);
		
		Rectangle *rect2 = new Rectangle(NULL, 106, 106, 64, 64, .6, .6, .6, 1, 1, 1, 4.0);
		Text *caption2 = new Text(NULL,106,106);
		
		caption->setFont("Calibri");
		caption->setFontSize(12);
		caption->setColor("#FFF");
		caption->setText("");
		//SelectableRectangle *selRect = new SelectableRectangle(NULL, 100, 100, 128, 128, .2, .2, .2, 1, 1, 1, 4.0,0,0,1,rect, caption);
		
		getTenUI()->addDisplayObject(rect);
		getTenUI()->addDisplayObject(caption);
		
		
		
		
		getTenUI()->addDisplayObject(rect2);
		getTenUI()->addDisplayObject(caption2);
		
		caption2->setFont("Calibri");
		caption2->setFontSize(12);
		caption2->setColor("#FFF");
		caption2->setText("child");
		//DraggableRectangle *drgRect = new DraggableRectangle(NULL, 106, 106, 64, 64, .2, .2, .2, 1, 1, 1, 4.0,0,0,1,rect2, caption2);
		
		//getTenUI()->addDisplayObject(selRect);
		//getTenUI()->addDisplayObject(drgRect);
		
		//TableInput_NewArch *tblNA = dynamic_cast<TableInput_NewArch*>(InputManager::getInput(1));
		/*if(tblNA != 0)
		{
			tblNA->horzBar = new Line(NULL, 0, 10, 5, 5,	//x,y,x2,y2
					1.0,0.0,0.0, 	// stroke color
					2.0);
			
			tblNA->vertBar = new Line(NULL, 5, 0, 5, 10,	//x,y,x2,y2
							1.0,0.0,0.0, 	// stroke color
							2.0);
			
			getTenUI()->addDisplayObject(tblNA->horzBar);
			getTenUI()->addDisplayObject(tblNA->vertBar);
		}*/
		//selRect->addChild(drgRect);
	}
	
	/*void TMMUI_TestApp::initInteractiveRectangleTest(){			
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
			
			getTenUI()->addDisplayObject(tmpRect2);
			getTenUI()->addDisplayObject(tmpRect);
						
		}*/
	
	/*void TMMUI_TestApp::initLineTest(){		
		Line *tmpLine;
		for(unsigned int i = 0; i < 1280; i+=64){
			for(unsigned int j = 0; j < 1024; j+=64){			
				tmpLine = new Line(NULL, (int)(i+((float)i/(1280.0-64))*64.0), (int)(j+((float)j/(1024.0-64))*64.0), (int)((i+64)-((float)i/(1280.0-64))*64.0), (int)((j+64)-((float)j/(1024.0-64))*64.0),	//x,y,x2,y2
										(float)((i)/1280.0), (float)((i+j)/1302.0), (float)((j)/1024.0), 	// stroke color
										(float)((double)i/(1280.0-64.0))*4+1.0);			//stroke size										 
				getTenUI()->addDisplayObject(tmpLine);
			}
		}
	}*/
	
	/*void TMMUI_TestApp::initRasterTest(){
		Rasterable *tmpRaster = new Rasterable(NULL, 1034,640);
		tmpRaster->setTextureFromFile("TestResources/RasterTest/bomber_red.png");
		
		getTenUI()->addDisplayObject(tmpRaster);
	}*/
	
	/*void TMMUI_TestApp::initTextTest(){
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
		
		
	}*/
	

	void TMMUI_TestApp::init() throw(int) {
		
		Rectangle *bg = new Rectangle(NULL, 0, 0, getScreenWidth(), getScreenHeight(), 1.0, 1.0, 1.0,1.0,1.0,1.0,1.0);
		getTenUI()->addDisplayObject(bg);
		
		initChildrenTest();
		//initLotsOfRectanglesTest();
		//initInteractiveRectangleTest();
		//initRectangleTest();
		//initLineTest();
		//initTextTest();
		//initRasterTest();						
	}
	
	void TMMUI_TestApp::update_frame() throw(APPEXCEPTIONS) {
	}
	
}




