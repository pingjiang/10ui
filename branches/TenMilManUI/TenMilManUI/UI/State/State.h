#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <tr1/functional>
#include <tr1/memory>

#include "StateMachineGlobals.h"
#include "StateMachine.h"

using std::string;

using std::tr1::function;
using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
using std::tr1::enable_shared_from_this;
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
		State(const shared_ptr<StateMachine>& , const string&);
		virtual ~State(){}
	
		const string& getID(){
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
