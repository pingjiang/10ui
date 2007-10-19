#ifndef SELECTMANAGER_H_
#define SELECTMANAGER_H_

#include "Manager.h"
#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <set>
#include "../../UserInputs/SDLMouseInput.h"
#include "../../UserInputs/TableInput.h"

using namespace std;

namespace TenUI{

	struct Input {
		int x, y;
		bool p;
	};

	class SelectManager : public Manager
	{
	public:
		SelectManager();
		virtual ~SelectManager();
		
		//map<long, set<UIComponent*> > selectedObjects;
		//map<long, set<UIComponent*> > pressedObjects;
		map<UserInput*,set<UIComponent*>* > allHoveredObjects; // obj hovered over
		//set<UIComponent*> hoveredObjects;
		
		//Input last_m, last_t;
		map<UserInput*, Input*> last_ui;
		//int last_x, last_y, new_x, new_y;
		//bool last_p, new_p;//, last_s, new_s;
		
		virtual void init()
		{
			set<UserInput*>* all_inputs = InputManager::getInputs();
			
			for(set<UserInput*>::iterator i = all_inputs->begin(); i != all_inputs->end(); ++i)
			{
				Input* tmpInput = new Input;
				set<UIComponent*>* tmpUIset = new set<UIComponent*>;
				last_ui.insert(make_pair(*i,tmpInput));
				allHoveredObjects.insert(make_pair(*i,tmpUIset));
			}
			
		}
		
		virtual bool update()
		{
			UserInput* ui;// = UserInput::instance();
			//set<UserInput*>* all_inputs = UserInput::getInputs();
			set<UserInput*>* all_inputs = InputManager::getInputs();
			
			set<UIComponent*>* hoveredObjects; // = allHoveredObjects.find(ui)->second;
			
			
			Input* last;
			
			int last_x = -1, last_y = -1, new_x, new_y;
			bool last_p = false, new_p;
			
			// update UserInput
			//ui->update();
			for(set<UserInput*>::iterator j = all_inputs->begin(); j != all_inputs->end(); ++j)
			{
				ui = (*j);
				last = last_ui.find(ui)->second;
				hoveredObjects = allHoveredObjects.find(ui)->second;
				
				last_x = last->x;
				last_y = last->y;
				last_p = last->p;
				/*if(ui->getType() == UserInput::MOUSE_INPUT)
				{
					last_x = last_m.x;
					last_y = last_m.y;
					last_p = last_m.p;
				}
				else if(ui->getType() == UserInput::TABLE_INPUT)
				{
					last_x = last_t.x;
					last_y = last_t.y;
					last_p = last_t.p;
				}*/
				
				
				new_x = ui->getX();
				new_y = ui->getY();
				
				new_p = ui->isPressed();
				
				// chg exists?
				// no
				if(new_x == last_x && new_y == last_y && \
				   new_p == last_p);
				// yes
				else
				{
					// package into Events for processing
					Event* evt = new Event;
					
					// hover events
					set<UIComponent*> alreadyHovered;
					set<UIComponent*> newHovered;
					set<UIComponent*> formerlyHovered;
					
					queue<string> evtNames;
					
					evt->x = new_x;
					evt->y = new_y;
					evt->pressed = new_p;
					
					if(new_p == last_p)
					// hover event; separate for each obj -> deals with ALL objs at x,y
					{
						//evtNames.push(UIComponent::HOVER_MOVE_EVENT);
					}
					// press event; only top obj @ x,y
					else if(new_p && !last_p)
					{
						evtNames.push(UIComponent::PRESS_EVENT);
					}
					// select/click event; only top obj @ x,y
					else if(last_p && !new_p)
					{
						evtNames.push(UIComponent::UNPRESS_EVENT);
						evtNames.push(UIComponent::CLICK_EVENT);
					}
	
					//long objID = 0;
	
					UIComponent* obj = 0;// = getObjectAtPoint(x,y);
					
					queue<UIComponent*> objs;// = getObjectsAtPoint(x,y);
					
					UIComponent* vtc; // verytempcomponent
					
					// ::obsolete::
					// process backwards, get the objs added most recently (which will be on top)
					//for(std::map<long,UIComponent*>::reverse_iterator i = registeredObjects.rbegin(); i != registeredObjects.rend(); ++i)
					
					for(std::map<long,UIComponent*>::iterator i = registeredObjects.begin(); i != registeredObjects.end(); ++i)
					{
						vtc = i->second;
						//cout << "Checking object " << i->first << "\n";
						
						if(new_x >= vtc->getX() && new_x <= (vtc->getX() + vtc->getW()) && \
						   new_y >= vtc->getY() && new_y <= (vtc->getY() + vtc->getH()))
						{
							//cout << "Found object " << i->first << "\n";
							objs.push(vtc);
							//objID = i->first;
							// once an object is found process
							//break;
						}
						//else { obj = 0; }
					}
					
					if(!objs.empty())
						obj = objs.back();
					else
						obj = 0;
					
					// if an object exists @ x,y
					//if(obj != 0)
					
					UIComponent* tmpComponent;
					
					
					while(!objs.empty())
					{
						tmpComponent = objs.front();
						objs.pop();
						
						if(hoveredObjects->find(tmpComponent) != hoveredObjects->end())
							// tmpComponent was already hovered -> HOVER_MOVE
							alreadyHovered.insert(tmpComponent);
						else
							// tmpComponent is a new hover -> HOVER_IN
							newHovered.insert(tmpComponent);
					}
					
					for(set<UIComponent*>::iterator i = hoveredObjects->begin(); i != hoveredObjects->end(); ++i)
					{
						if(alreadyHovered.find(*i) == alreadyHovered.end() )
							// *i isn't hovered anymore -> HOVER_OUT
							formerlyHovered.insert(*i);
					}
					
					hoveredObjects->clear();
					
					Event tmpEvt(UIComponent::HOVER_MOVE_EVENT, evt->x, evt->y, evt->pressed);
					for(set<UIComponent*>::iterator i = alreadyHovered.begin(); i != alreadyHovered.end(); ++i)
					// HOVER_MOVE
					{
						(*i)->dispatchEvent(&tmpEvt);
						
						hoveredObjects->insert(*i);
					}
					
					tmpEvt.evtName = UIComponent::HOVER_IN_EVENT;
					for(set<UIComponent*>::iterator i = newHovered.begin(); i != newHovered.end(); ++i)
					// HOVER_IN
					{
						(*i)->dispatchEvent(&tmpEvt);
						
						hoveredObjects->insert(*i);
					}
					
					//allHoveredObjects[ui] = hoveredObjects;
					
					tmpEvt.evtName = UIComponent::HOVER_OUT_EVENT;
					for(set<UIComponent*>::iterator i = formerlyHovered.begin(); i != formerlyHovered.end(); ++i)
						// HOVER_OUT
						(*i)->dispatchEvent(&tmpEvt);
					
					
						//objID = obj->getObjectID(); << done already
						//std::cout << "\t\t\t\tChecking obj(" << obj->getObjectID() << ")\n";
						//tell UIComponent to deal with it (possibly them for multiple events)
					
					while(obj != 0 && !evtNames.empty())
					{
						// set temp event's name to the first on the stack
						evt->evtName = evtNames.front();
						evtNames.pop();
						// send off the event and go on to the next one
						obj->dispatchEvent(evt);
					}
				}
				
				last_x = new_x;
				last_y = new_y;
				last_p = new_p;
				
				last->x = last_x;
				last->y = last_y;
				last->p = last_p;
				/*if(ui->getType() == UserInput::MOUSE_INPUT)
				{
					last_m.x = last_x;
					last_m.y = last_y;
					last_m.p = last_p;
				}
				else if(ui->getType() == UserInput::TABLE_INPUT)
				{
					last_t.x = last_x;
					last_t.y = last_y;
					last_t.p = last_p;
				}*/
								
				//last_s = new_s;
			}
			
			return true;
		}
	};
}

#endif /*SELECTMANAGER_H_*/
