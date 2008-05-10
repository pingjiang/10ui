#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include "DisplayObjectContainer.h"

#include <TenMilManUI/UI/Core/States/UIComponentState.h>

#include <TenMilManUI/UI/Managers/StyleManager.h>

#include <TenMilManUI/UI/State/StateMachine.h>
#include <TenMilManUI/UI/State/StateMachineEvent.h>

#include <TenMilManUI/UI/Style/StyleSet.h>

#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/UserInput_Globals.h>

#include <TenMilManUI/UI/State/StateMacros.h>
#include <TenMilManUI/UI/Style/StyleMacros.h>
#include <TenMilManUI/UI/Core/Macros/EventMacros.h>
#include "UIComponentMacros.h"


#include <iostream>
#include <map>
#include <boost/any.hpp>

using std::cout;
using std::endl;

using boost::any;

namespace TenUI {	
	
	class UserInputEvent;
	class UIComponentState;

	class UIComponent : public DisplayObjectContainer {
	friend class UIComponentTransition;
	
	BEGIN_DECLARE_EVENTS(UIComponent,DisplayObjectContainer)
		DECLARE_EVENT(UIComponent, MultiPointEvent)
		DECLARE_EVENT(UIComponent, PointIn)
		DECLARE_EVENT(UIComponent, PointOut)
		DECLARE_EVENT(UIComponent, PointMove)
		DECLARE_EVENT(UIComponent, PointUp)
		DECLARE_EVENT(UIComponent, PointDown)
	END_DECLARE_EVENTS(UIComponent)
	
	public: 
		static string 			getUICompName(){ return "UIComponent"; }
		
	protected:
								UIComponent(int x=0, int y=0, unsigned int w=100, unsigned int h=100)
									:DisplayObjectContainer(sp<DisplayObject>(), x,y ,w,h, 0.0,1.0,1.0){
								}
			
	public:
		virtual 				~UIComponent(){};
					
	/***********************************/
	/*              Input  		       */
	/***********************************/
	private:
		UserID_Type			 	ownerUserID;
	public:
		UserID_Type			 	getOwnerUserID();
		void 					setOwnerUserID(UserID_Type newOwner);
		UserID_Type			 	clearOwnerUserID();
		
	public:
		virtual void 			handleUserInputEvent(const sp<UserInputEvent>& uievent);
			
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	public:
		static StateIDType		getStartStateID();
		const string& 			getCurState();
		const sp<StateMachine>& getStateMachine();
		
	protected:
		sp<StateMachine> 		stateMachine;

	/***********************************/
	/*        	    Style  			   */
	/***********************************/
	public:
		void 					 setAllStateStyleValue(const string& name, const any& newvalue);
		any  					 getStateStyleValue(const StateIDType& stateid, const string& name);
		void 					 setStateStyleValue(const StateIDType& stateid, const string& name, const any& newvalue);
		any 					 getStyleValue(const string& name );
		void 					 setStyleValue(const string& name, const any& newvalue);
		
	protected:
		sp< StyleSet > 								curStyleSet;
		unordered_map< StateIDType, sp<StyleSet> >	stateStyleSetMap;

		void 					 setStyleSet(const string& styleSetName);
	
	/***********************************/
	/*        Game Loop Methods        */
	/***********************************/
	public:
		virtual void 			 init();
		virtual void 			 drawSelf();
		virtual void 		  	 update();
		
	};
}

#endif /*UICOMPONENT_H_*/
