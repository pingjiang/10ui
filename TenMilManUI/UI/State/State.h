#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <tr1/functional>
#include <TenMilManUI/Util/SmartPointer.h>

#include "StateMachineGlobals.h"
#include "StateMachine.h"

using std::string;

using std::tr1::function;

namespace TenUI {
	class StateMachine;
	
	class State : public enable_shared_from_this<State> {
		/***************************************
		 *       Public Types Definitions      *
		 ***************************************/ 
	public:
		static const StateIDType 					ANY_STATE;
	
		/***************************************
		 *       	  Public Methods           *
		 ***************************************/
	public:
		State(const string&);
		virtual ~State(){}
	
		void setStateMachine(const sp<StateMachine>& sm){
			stateMachine = sm;
		}
		
		const StateIDType& getID(){
			return id;
		}
		
		virtual void onEnter(const StateIDType& prevState) = 0;
		virtual void update() = 0;
		virtual void onExit(const StateIDType& nextState) = 0;
		
		
		/***************************************
		*            Helper Functions          *
		****************************************/
	protected:
		bool exitState(const StateIDType& nextState);
			
		
		/***************************************
		*           Private Variables          *
		****************************************/
	private:
		weak_ptr<StateMachine> stateMachine;  
		StateIDType id;	
			
		/***************************************
		 *       	 Private Methods           *
		 ***************************************/
	private:
		
	};
}

#endif /*STATE_H_*/
