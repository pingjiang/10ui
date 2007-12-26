#ifndef UICONTROLS_TESTAPP_H_
#define UICONTROLS_TESTAPP_H_

#include <iostream>
#include <string>

#include <TenMilManUI/ITenUIApp.h>
#include <TenMilManUI/TenUI.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/OpenGL_Graphics/OpenGL_Graphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>

using namespace std;

namespace TenUI {

	class UIControls_TestApp : public ITenUIApp {
		/***************************************/
		/************ Public Methods ***********/
		/***************************************/
		public:
			UIControls_TestApp(){}
			virtual ~UIControls_TestApp(){}		
		

		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
			/**
			 * Factory Method that creates a military unit
			 * @param 	picPath		String holding file path to image to be used as picture.
			 * @param 	x			starting x coordinate
			 * @param 	y			starting y coordinate
			 * @param 	w			starting width
			 * @param 	h			starting height
			 */
			shared_ptr<UIComponent>	createPicture(const string& picPath, int x, int y, int w, int h);
			
		/***************************************/
		/**** ITenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual IGraphics* initGraphics();
			virtual void initUserInputs();
			virtual void init();
			virtual void deinit(){}
			
			virtual void update_preframe(){}
			virtual void update_frame(){}
	};
	
}

#endif /*UICONTROLS_TESTAPP_H_*/
