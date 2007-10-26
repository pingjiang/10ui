#ifndef INTERACTIVERECTANGLE_H_
#define INTERACTIVERECTANGLE_H_

#include <iostream>
#include "../../Graphics/Vector/Rectangle.h"
#include "../Core/UIComponent.h"

using namespace std;

namespace TenUI
{

class InteractiveRectangle : public UIComponent
{
public:
	Rectangle* rect;
	
	InteractiveRectangle(DisplayObject *p, int x=0, int y=0, int w=0, int h=0, float r=0.0, float g=0.0, float b=0.0, float sr=0.0, float sg=0.0, float sb=0.0, float strSize=0.0, double rot=0.0, double s=1.0, double o=1.0, Rectangle* target=NULL)
	: UIComponent(p,x,y,w,h,rot,s,o)
	{
		rect = target; //new Rectangle(this,0,0,w,h,r,g,b,sr,sg,sb,strSize,rot,s,o);
		
		this->addEvtHandler(UIComponent::CLICK_EVENT,this);
		this->addEvtHandler(UIComponent::UNPRESS_EVENT,this);
		this->addEvtHandler(UIComponent::PRESS_EVENT,this);
		this->addEvtHandler(UIComponent::HOVER_IN_EVENT,this);
		this->addEvtHandler(UIComponent::HOVER_OUT_EVENT,this);
		this->addEvtHandler(UIComponent::HOVER_MOVE_EVENT,this);
		
		//debugging
		//this->displayEvtHandlers();
	}
	
	
	
	virtual ~InteractiveRectangle();
	
	virtual void init(){
		
		//addChild(rect);
	}
	
	virtual void update(){}
	
	virtual bool handleEvent(Event* evt)
	{
		if(evt->evtName == UIComponent::CLICK_EVENT)
		// onMouseClick
		{
			cout << "InteractiveRectangle::CLICK_EVENT(" << evt->x << "," << evt->y << "," << evt->pressed << ")\n";
			//rect->setX(rect->getX() + 10);
			//this->setX(this->getX() + 10);
		}
		else if(evt->evtName == UIComponent::PRESS_EVENT)
		// onMouseDown
		{
			cout << "InteractiveRectangle::PRESS_EVENT(" << evt->x << "," << evt->y << "," << evt->pressed << ")\n";
			
		}
		else if(evt->evtName == UIComponent::UNPRESS_EVENT)
		// onMouseUp
		{
			
			cout << "InteractiveRectangle::UNPRESS_EVENT(" << evt->x << "," << evt->y << "," << evt->pressed << ")\n";	
		}
		else if(evt->evtName == UIComponent::HOVER_IN_EVENT)
		// onMouseEnter
		{
			cout << "InteractiveRectangle::HOVER_IN_EVENT(" << evt->x << "," << evt->y << "," << evt->pressed << ")\n";
			//rect->setRotation(rect->getRotation() + 20);
			float r,g,b;
			rect->getFillColor(r,g,b);
			rect->setFillColor(2*r,2*g,2*b);
		}
		else if(evt->evtName == UIComponent::HOVER_OUT_EVENT)
		// onMouseExit
		{
			cout << "InteractiveRectangle::HOVER_OUT_EVENT(" << evt->x << "," << evt->y << "," << evt->pressed << ")\n";
			//rect->setRotation(rect->getRotation() - 20);
			float r,g,b;
			rect->getFillColor(r,g,b);
			rect->setFillColor(.5*r,.5*g,.5*b);
		}
		else if(evt->evtName == UIComponent::HOVER_MOVE_EVENT)
		// onMouseMove
		{
			//cout << "InteractiveRectangle::HOVER_MOVE_EVENT(" << evt->x << "," << evt->y << "," << evt->pressed << ")\n";
			//rect->setRotation(rect->getRotation() - 2);
			
		}
		
		return true;
	}
};

}

#endif /*INTERACTIVERECTANGLE_H_*/
