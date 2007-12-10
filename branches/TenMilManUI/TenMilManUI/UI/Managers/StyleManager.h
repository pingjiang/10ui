#ifndef STYLEMANAGER_H_
#define STYLEMANAGER_H_

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Style/StyleSetDeclaration.h>
#include <TenMilManUI/UI/State/State.h>


#include <string>
#include <tr1/unordered_map>
#include <tr1/memory>

using std::string;
using std::tr1::unordered_map;
using std::tr1::shared_ptr;

namespace TenUI{

	class UIComponent;

	typedef unordered_map< string, shared_ptr<StyleSetDeclaration> > 			State_StyleDeclaration_MapType;
	typedef unordered_map< string, shared_ptr<StyleSet> > 						State_Style_MapType; 
	typedef unordered_map< string, shared_ptr<State_StyleDeclaration_MapType> > UIComp_StateStyle_MapType;
			
	class StyleManager {		
	public:
		static shared_ptr<StyleManager> instance();

	public:
		UIComp_StateStyle_MapType compStyleMap;
		
	public:
		virtual ~StyleManager();
		
		void registerUIComponent(shared_ptr<UIComponent> uiComps, const string& uiCompName, const string& parentUICompName);	
		void addStyleDeclaration(const string& uiCompName, const shared_ptr<StyleDeclaration>& styleDecl);
		void setStyleDeclaration(const string& uiCompName, const shared_ptr<StyleDeclaration>& styleDecl);
		void setStateStyleDeclaration(const string& uiCompName, const StateIDType& stateid,const shared_ptr<StyleDeclaration>& styleDecl);
		shared_ptr< State_Style_MapType > getStateStyleSetMap(const string& uiCompName);
		
	private:
		StyleManager();
		static shared_ptr<StyleManager> inst;
		
		
	};
	
}

#endif /*STYLEMANAGER_H_*/
