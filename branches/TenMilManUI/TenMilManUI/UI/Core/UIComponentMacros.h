#ifndef UICOMPONENTMACROS_H_
#define UICOMPONENTMACROS_H_

#include <string>
#include <tr1/functional>
#include "UIComponent.h"

#include <TenMilManUI/UI/Managers/UIComponentManager.h>
#include <TenMilManUI/UI/Managers/StateManager.h>
#include <TenMilManUI/UI/Managers/StyleManager.h>

using std::string;
using std::tr1::function;

#define DECL_UICOMP(uiCompName, super_uiCompName) 										\
	public:																				\
		static string getUICompName(){ return #uiCompName; }							\
		static string getSuperUICompName(){ return super_uiCompName::getUICompName(); }	\
		static sp<UIComponent> create();												\
		static function< sp<UIComponent> () > getCreateFunction();						\
		static const bool _uicompinit_helper;											\
		static bool _uicompinit();														\
	protected:																			\
		uiCompName(){}																	\
	private:																			\
		void _init();
		
#define IMPL_UICOMP(uiCompName) 														\
		function< sp<UIComponent> () > uiCompName::getCreateFunction()	{				\
			return &uiCompName::create;													\
		}																				\
		bool uiCompName::_uicompinit(){													\
			UIComponentManager::instance()->registerUIComponent(						\
				uiCompName::getUICompName(),											\
				uiCompName::getSuperUICompName(),										\
				uiCompName::getCreateFunction() );										\
			StateManager::instance()->registerUIComponent(uiCompName::getUICompName()); \
			StyleManager::instance()->registerUIComponent(uiCompName::getUICompName()); \
			return false;																\
		}																				\
		const bool uiCompName::_uicompinit_helper = uiCompName::_uicompinit();			\
		sp<UIComponent> uiCompName::create(){											\
			sp<uiCompName> newUIComp(new uiCompName());									\
			newUIComp->initEvents();													\
			newUIComp->_init();															\
			newUIComp->init();															\
			return newUIComp;															\
		}																				\
		void uiCompName::_init(){														\
			stateMachine = StateManager::instance()->createStateMachine( uiCompName::getUICompName(), dynamic_pointer_cast<UIComponent>(shared_from_this()) ); \
			sp<StyleSet> styleSet = StyleManager::instance()->getStyleSet( uiCompName::getUICompName() ); \
			sp< unordered_set<StateIDType> > stateids = stateMachine->getStateIDs();	\
			for( unordered_set<StateIDType>::iterator sit = stateids->begin();			\
				 sit != stateids->end();												\
				 ++sit){																\
					stateStyleSetMap[(*sit)] = styleSet->clone();						\
			}																			\
			curStyleSet = stateStyleSetMap[stateMachine->getCurState()->getID()]; 		\
		}
		
#endif /*UICOMPONENTMACROS_H_*/
