#ifndef UICOMPONENTMANAGER_H_
#define UICOMPONENTMANAGER_H_

#include <string>
#include <TenMilManUI/Util/SmartPointer.h>
#include <TenMilManUI/UI/Core/UIComponent.h>

#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace TenUI{

	class UIComponent;

	/**
	 * A registry of UIComponent types.
	 */
	class UIComponentManager {

	/**
	 * @name Singleton Implementation
	 */
	//@{
	public:
		/**
		 * Creates a new singleton instance of UIComponentManager.
		 */
		static sp<UIComponentManager> instance();
	
	private:
		UIComponentManager();
	//@}
		
	private:
		typedef function< sp<UIComponent> () > 				CreateFunc_Type;
		typedef unordered_map< string, CreateFunc_Type > 	Name_CreateFunc_MapType;
		typedef unordered_map< string, string > 			SuperName_MapType;
		
		Name_CreateFunc_MapType	nameCreateFuncMap;
		SuperName_MapType		superNameMap;
				
	public:
		virtual 		~UIComponentManager();

		void 			registerUIComponent(const string& name, const string& superName, const CreateFunc_Type& createFunc);
		
		bool 			hasRegistered(const string& name);		
		bool 			isRootUIComponent(const string& name);		
		string 			getSuperUIComponent(const string& name);		
		sp<UIComponent> createUIComponent(const string& name);
		
	};
}

#endif /*UICOMPONENTMANAGER_H_*/
