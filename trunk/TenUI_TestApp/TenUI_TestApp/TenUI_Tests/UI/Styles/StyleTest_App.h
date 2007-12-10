#ifndef STYLETEST_APP_H_
#define STYLETEST_APP_H_

#include <iostream>
#include <string>

#include <TenMilManUI/ITenMilManUIApp.h>
#include <TenMilManUI/TenMilManUI.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/OpenGL_Graphics/OpenGL_Graphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>


using namespace std;

namespace TenUI {

	class StyleTest_App : public ITenMilManUIApp {
		
		/***************************************/
		/************ Public Methods ***********/
		/***************************************/
		public:
			StyleTest_App();
			virtual ~StyleTest_App(){}		

		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:
			template<class StyleDataType> 
			bool test_ParseData_ToString(StyleDataType* styleData, const string& parseableString, const string& toStringResult);

			template<class StyleDataType> 
			bool test_Clone(StyleDataType* styleData);

			template<class StyleDataType> 
			void test_StyleData(const string& sdataName, const string& parseData, const string& toStringResult);
			

			template<class StyleDataType, typename DataType>
			void testSingleStyle(	const string& styleName, 
									DataType initValue,
									const string& parseData, 
									const string& toStringResult	);

			template<class StyleDataType, typename DataType>
			void testArrayStyle(	const string& styleName, 
									DataType initValues[],
									int size,
									const string& parseData, 
									const string& toStringResult	);
			
		/***************************************/
		/**** ITenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual void init() throw(int){}
			virtual void update_preframe() throw(APPEXCEPTIONS){}
			virtual void update_frame() throw(APPEXCEPTIONS);
			virtual void deinit() throw(APPEXCEPTIONS) {}
			
			virtual char* getName()								{ return "StyleTest App"; }
			
			virtual GraphicsOptions* getGraphicsOptions() 		{ return new GraphicsOptions(	1024, 768, 32, 
																	  				 			IGraphicsEnums::WINDOWED, 
																	  				 			string("")); 		}
			virtual IGraphics* getGraphics()					{ return OpenGL_Graphics::instance(); }
			
			virtual UserInput* getUserInput()					{ return SDLMouseInput::createInstance(); }
	};
	
}

#endif /*STYLETEST_APP_H_*/
