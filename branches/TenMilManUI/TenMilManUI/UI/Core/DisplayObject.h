// display object is an object to be displayed on the screen.
// it gets extended by other types of display objects such
// as libraryobjects, transformable objects, and selectedobjects.

#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

// includes
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <math.h>
#include <string>

#include <tr1/memory>

#include <TenMilManUI/UI/Events/EventDispatcher.h>

using std::tr1::shared_ptr;
using std::tr1::enable_shared_from_this;

namespace TenUI {
	
	typedef unsigned long DisplayObjectIDType;

	class DisplayObject : public EventDispatcher, public enable_shared_from_this<DisplayObject>  {
	private:
		static DisplayObjectIDType nextObjectID;
	
	protected:
		DisplayObjectIDType objid;

		/***********************************/
		/*         Member Variables        */
		/***********************************/
			// Hierarchy
			shared_ptr<DisplayObject> parent;
			
			// Enable/Disable
			bool enabled;
		
			// Positioning
			int x;
			int y;
			
			// Sizing 
			unsigned int w;
			unsigned int h;
							
			// Scaling
			double scalex;
			double scaley;
	
			// Rotation
			double rotation;
		
			// Visibility
			float opacity;
			bool visible;
							
			// OpenGL implementation specifics
			//GLint viewport[4];
			//GLdouble modelview[16];
			//GLdouble projection[16];
			
			int centerx;
			int centery;		
	
			double left;
			double bottom;
		
		// recalc centerx, centery
		virtual void calcCenterX();	
		virtual void calcCenterY();		
		
	public:
		
		// constructor
		DisplayObject( const shared_ptr<DisplayObject>& p, int x, int y, unsigned int w, unsigned int h, double r=0.0, double s=1.0, float o=1.0);	
		virtual ~DisplayObject(){}
			
		/***********************************/
		/*        Init/Update Methods      */
		/***********************************/
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void deinit() = 0;
		
		/***********************************/
		/*           Draw Methods          */
		/***********************************/
			// Pushes View Matrix 
			virtual void preDraw();
			// Draws Object (subclassed)
			virtual void draw() = 0;
			// Pops View Matrix
			virtual void postDraw();
		

		/***********************************/
		/*     Hierarchy Getter/Setters    */
		/***********************************/  
		unsigned long 			getObjectID();
		
		shared_ptr<DisplayObject>	getParent();		
		void 						setParent(const shared_ptr<DisplayObject>& p);
	
		bool 			getEnabled();
		void 			setEnabled(bool e);
		

		/***********************************/
		/*    Dimensions Getters/Setters   */
		/***********************************/  
		virtual unsigned int 	getW();
		virtual void 			setW(unsigned int nw);	
		virtual unsigned int 	getH();
		virtual void 			setH(unsigned int nh);	


		/***********************************/
		/*    Visibility Getter/Setters    */
		/***********************************/  
		bool 	getVisible();
		void 	setVisible(bool e);		
		double 	getOpacity();		
		void 	setOpacity(float o);
			
		/***********************************/
		/*  Transformation Getter/Setters  */
		/***********************************/

			/*****************/
			/*  Translation  */
			/*****************/
			virtual void 	setCenterX(int nx);			
			virtual void 	setCenterY(int ny);
			
			virtual void 	setX(int nx);
			virtual int 	getX();			
			virtual void 	setY(int ny);
			virtual int 	getY();			
					double 	getGlobalX();
					double 	getGlobalY();			

			/*****************/
			/*    Rotation   */
			/*****************/
			double 	getRotation();
			void 	setRotation(double r);
			
			/*****************/
			/*      Scale    */
			/*****************/		
			double 	getScaleX();
			void 	setScaleX(double s);			
			double 	getScaleY();
			void 	setScaleY(double s);
				
		//void globalToLocalCoord(int sx, int sy, double *ox, double *oy);	
		//void localToGlobalCoord(int sx, int sy, int *ox, int *oy);
	
	};

}

#endif
