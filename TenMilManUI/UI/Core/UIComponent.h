#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include "DisplayObjectContainer.h"
#include <TenMilManUI/UI/Managers/StyleManager.h>
#include <TenMilManUI/UI/State/StateMachine.h>
#include <TenMilManUI/UI/State/StateMachineEvent.h>
#include <TenMilManUI/UI/Style/StyleSet.h>

#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>

#include <iostream>
#include <map>
#include <tr1/memory>
#include <boost/any.hpp>

using std::cout;
using std::endl;
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

using boost::any;

namespace TenUI {	
	
	class UserInputEvent;

	class UIComponent : public DisplayObjectContainer {
	friend class UIComponentTransition;
	public:
								 UIComponent(int x, int y, unsigned int w=100, unsigned int h=100)
								 	:DisplayObjectContainer(shared_ptr<DisplayObject>(), x,y ,w,h, 0.0,1.0,1.0){
									 stateMachine = shared_ptr<StateMachine>(new StateMachine());
								 }
		virtual 				 ~UIComponent(){};	

		// UIComponent Identification
		virtual string 			 getUIComponentName();
		
	/***********************************/
	/*              Input  		       */
	/***********************************/
		virtual void 			 handleUserInputEvent(const shared_ptr<UserInputEvent>& uievent);
		
	/***********************************/
	/*              Event  		       */
	/***********************************/
	protected:
		virtual void 			 initEvents();
	
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	public:
		const string& 			 getCurState();
		const shared_ptr<StateMachine>& getStateMachine();
		
	protected:
		shared_ptr<StateMachine> stateMachine;

		virtual void 			 initStates();

	/***********************************/
	/*        	    Style  			   */
	/***********************************/
	public:
		any  					 getStateStyleValue(const StateIDType& stateid, const string& name);
		void 					 setStateStyleValue(const StateIDType& stateid, const string& name, const any& newvalue);
		any 					 getStyleValue(const string& name );
		void 					 setStylevalue(const string& name, const any& newvalue);
		
	protected:
		shared_ptr< StyleSet > 											curStyleSet;
		shared_ptr< unordered_map< string, shared_ptr<StyleSet> >  > 	stateStyleSetMap;

		virtual void 			 initStyles();
		void 					 loadStyleSetMap();
		void 					 setStyleSet(const string& styleSetName);
	
	/***********************************/
	/*        Game Loop Methods        */
	/***********************************/
	public:
		virtual void 			 drawSelf();
		virtual void 		  	 init();
		virtual void 		  	 update();
		
	};
}

#endif /*UICOMPONENT_H_*/
