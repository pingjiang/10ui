#ifndef STYLEMANAGER_H_
#define STYLEMANAGER_H_

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Style/StyleSetDeclaration.h>
#include <TenMilManUI/UI/State/State.h>
#include <TenMilManUI/Util/SmartPointer.h>

#include <string>
#include <tr1/unordered_map>

using std::string;
using std::tr1::unordered_map;

namespace TenUI{

	class UIComponent;

	typedef unordered_map< string, sp<StyleSetDeclaration> > 			State_StyleDeclaration_MapType;
	typedef unordered_map< string, sp<StyleSetDeclaration> > 			UIComp_StyleDeclaration_MapType;
	typedef unordered_map< string, sp<StyleSet> > 						State_Style_MapType; 
	typedef unordered_map< string, sp<State_StyleDeclaration_MapType> > UIComp_StateStyle_MapType;
			
	class StyleManager {		
	public:
		static sp<StyleManager> instance();

	public:
		UIComp_StyleDeclaration_MapType compStyleMap;
		
		
	public:
		virtual ~StyleManager();
		
		void registerUIComponent(const string& uiCompName);
		bool hasRegistered(const string& uiCompName);
		void addStyleDeclaration(const string& uiCompName, const sp<StyleDeclaration>& styleDecl);
		void setStyleDeclaration(const string& uiCompName, const sp<StyleDeclaration>& styleDecl);
		sp< StyleSet > getStyleSet(const string& uiCompName);
		
	private:
		StyleManager();		
		
	};
	
}

#endif /*STYLEMANAGER_H_*/
