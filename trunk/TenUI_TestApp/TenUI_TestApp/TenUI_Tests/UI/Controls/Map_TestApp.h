#ifndef MAP_TESTAPP_H_
#define MAP_TESTAPP_H_

#include <iostream>
#include <string>

#include <TenMilManUI/ITenUIApp.h>
#include <TenMilManUI/TenUI.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/OpenGL_Graphics/OpenGL_Graphics.h>
#include <TenMilManUI/UI/Controls/DraggableButton/DraggableButton.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>

using namespace std;

namespace TenUI {

	class Map_TestApp : public ITenUIApp {
		/***************************************/
		/************ Public Methods ***********/
		/***************************************/
		public:
			Map_TestApp(){}
			virtual ~Map_TestApp(){}		
			
		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:
			shared_ptr<UIComponent> mapui;
			
			/**
			 * Factory Method that creates the map
			 * @param 	mapImage	String holding file path to image to be used as map.
			 * @param 	x			starting x coordinate
			 * @param 	y			starting y coordinate
			 * @param 	w			width
			 * @param 	w			height 
			 */
			shared_ptr<UIComponent> createMap(const string& mapImage, int x, int y, int w, int h);
			
			/**
			 * Factory Method that creates a military unit
			 * @param 	isRed		True if red, False if blue unit
			 * @param 	unitIcon	String holding file path to image to be used as unit's icon.
			 * @param 	x			starting x coordinate
			 * @param 	y			starting y coordinate
			 */
			shared_ptr<UIComponent>	createUnit(bool isRed, const string& unitIcon, int x, int y);

		/***************************************/
		/**** ITenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual IGraphics* initGraphics();
			virtual void initUserInputs();
			virtual void init();
			virtual void deinit(){}
			
			virtual void update_preframe(){}
			virtual void update_frame();
	};
	
}

#endif /*MAP_TESTAPP_H_*/
