#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <math.h>
#include <string>

#include <tr1/functional>
#include <tr1/memory>

#include <TenMilManUI/UI/Events/EventDispatcher.h>

using std::tr1::shared_ptr;
using std::tr1::enable_shared_from_this;

using std::tr1::bind; 
using std::tr1::function;

namespace TenUI {
	
	typedef unsigned long DisplayObjectIDType;

	/** 
	 * Base Abstract class all displayable objects. 
	 * Contains basic properties all displayable objects will have:
	 * - Object ID
	 * - Width, Height
	 * - X, Y
	 * - Scale
	 * - Rotation
	 * 
	 * Defines virtual methods that subclasses must override
	 * - init
	 * - deinit
	 * - update
	 * - draw
	 */
	class DisplayObject : public EventDispatcher, public enable_shared_from_this<DisplayObject>  {
		
	public:
		/**
		 * Virtual Destructor
		 */
		virtual ~DisplayObject(){}
		
		/**
		 * @name Initialization/Deinitialization
		 * Functions that maintain initialization and deinitialization of the DisplayObject.
		 */
		//@{
		protected:	
			/**
			 * Subclasses must override this method to initialize self.
			 * This method is called on creation.
			 */
			virtual void init()   = 0;
		public:
			/**
			 * Subclasses must override this method to deinitialize self.
			 * This method is called before removal from TenUI.
			 */
			virtual void deinit() = 0;
		//@}
			
		/**
		 * @name Update/Drawing
		 * Functions that maintain updating and drawing of the DisplayObject.  
		 * When TenUI loops through DisplayObjects, these functions are called for each DisplayObject in this order:
		 * -# update
		 * -# preDraw
		 * -# draw
		 * -# postDraw
		 */
		//@{
		public:
			/**
			 * Subclasses must override this method to update self.
			 * This method is called before drawing occurs.
			 */
			virtual void update() = 0;
			/**
			 * Sets up view for drawing.
			 * This would include setting the views location, rotation, and scale
			 */
			virtual void preDraw();
			/**
			 * Subclasses must override this method to specify how to draw itself
			 */
			virtual void draw() = 0;
			/**
			 * Resets the view to a state before drawing
			 */
			virtual void postDraw();
		//@}

		/** 
		 * @name Identification
		 */
		//@{
			/**
			 * Gets DisplayObject's Unique Object ID.
			 */
			DisplayObjectIDType	getObjectID();
		//@}
		

		/** 
		 * @name Hierarchy
		 */
		//@{
			/** 
			 * Gets the DisplayObject that contains this DisplayObject
			 */
			shared_ptr<DisplayObject>	 	getParent();
			/** 
			 * Sets the DisplayObject that contains this DisplayObject
			 * @param p 	new parent of this DisplayObject
			 */
			void 						 	setParent(const shared_ptr<DisplayObject>& p);
		//@}
		
		bool 							getEnabled();
		void 							setEnabled(bool e);
		

		/** 
		 * @name Dimensions
		 */
		//@{
		public:
			/**
			 * Conveniency function to set Width and Height.
			 * @param nw	new width
			 * @param nh	new height
			 */
			virtual void 			setWH(unsigned int nw, unsigned int nh);
	
			/**
			 * Gets the width.
			 * @return	DisplayObject's width.
			 */
			virtual unsigned int 	getW();
			/**
			 * Sets the width.
			 * @param nw new width.
			 */
			virtual void 			setW(unsigned int nw);
			/**
			 * Gets the height.
			 * @return	DisplayObject's height.
			 */	
			virtual unsigned int 	getH();
			/**
			 * Sets the height.
			 * @param nh new height.
			 */
			virtual void 			setH(unsigned int nh);	
		//@}


		/** 
		 * @name Visibility
		 */
		//@{
		public:
			/**
			 * Gets opacity value.
			 * 0.0 is totally transparent
			 * 1.0 is opaque
			 */
			double 	getOpacity();		
			/**
			 * Sets opacity value.
			 * 0.0 is totally transparent
			 * 1.0 is opaque
			 * @param o new opacity value
			 */
			void 	setOpacity(float o);
		//@}
			
		
		/** 
		 * @name Positioning
		 * Functions that maintain the DisplayObject's position from different anchor points and global/local perspectives.
		 * A DisplayObject's position can be set based the Bottom-Left or Center anchor points.
		 * A DisplayObject's position can be set in terms global (or screen) or local coordinates.
		 * Local coordinates are relative to the parent.
		 */
		//@{
		public:
			/**
			 * Conveniency function for setting the X-Y position in terms of Global positioning and from the DisplayObject's Center anchor point.
			 */
			void 	setGlobalCenterXY(int cx, int cy);

			/**
			 * Sets the X position in terms of Global positioning and from the DisplayObject's Center anchor point.
			 * @param cx new global, center x coordinate
			 */
			void 	setGlobalCenterX(int cx);
			/**
			 * Sets the y position in terms of Global positioning and from the DisplayObject's Center anchor point. 
			 * @param cy new global, center y coordinate
			 */
			void 	setGlobalCenterY(int cy);

			/**
			 * Gets the X position in terms of Global positioning and from the DisplayObject's Center anchor point.
			 * @return global, center x coordinate
			 */
			int 	getGlobalCenterX();
			/**
			 * Gets the y position in terms of Global positioning and from the DisplayObject's Center anchor point.
			 * @return global, center y coordinate
			 */
			int 	getGlobalCenterY();


			/**
			 * Conveniency function for setting the X-Y position in terms of Local positioning and from the DisplayObject's Center anchor point.
			 */
			virtual void 	setCenterXY(int nx, int ny);
			/**
			 * Sets the X position in terms of Local positioning and from the DisplayObject's Center anchor point.
			 * @param nx new global, center x coordinate
			 */		
			virtual void 	setCenterX(int nx);	
			/**
			 * Sets the y position in terms of Local positioning and from the DisplayObject's Center anchor point. 
			 * @param ny new global, center y coordinate
			 */		
			virtual void 	setCenterY(int ny);
			/**
			 * Gets the x position in terms of Local positioning and from the DisplayObject's Center anchor point.
			 * @return global, center x coordinate
			 */
			virtual int 	getCenterX();
			/**
			 * Gets the y position in terms of Local positioning and from the DisplayObject's Center anchor point.
			 * @return global, center y coordinate
			 */
			virtual int 	getCenterY();

			/**
			 * Conveniency function for setting the X-Y position in terms of Local positioning and from the DisplayObject's Bottom-Left anchor point.
			 */
			virtual void 	setXY(int nx, int ny);
			/**
			 * Sets the X position in terms of Local positioning and from the DisplayObject's Bottom-Left anchor point.
			 * @param nx new global, center x coordinate
			 */		
			virtual void 	setX(int nx);
			/**
			 * Gets the x position in terms of Local positioning and from the DisplayObject's Bottom-Left anchor point.
			 * @return global, center x coordinate
			 */
			virtual int 	getX();		
			/**
			 * Sets the y position in terms of Local positioning and from the DisplayObject's Bottom-Left anchor point. 
			 * @param ny new global, center y coordinate
			 */			
			virtual void 	setY(int ny);
			/**
			 * Gets the y position in terms of Local positioning and from the DisplayObject's Bottom-Left anchor point.
			 * @return global, center y coordinate
			 */
			virtual int 	getY();
			
			/**
			 * Gets the y position in terms of Global positioning and from the DisplayObject's Bottom-Left anchor point.
			 * @return global, center y coordinate
			 */
					double 	getGlobalX();

			/**
			 * Gets the y position in terms of Global positioning and from the DisplayObject's Bottom-Left anchor point.
			 * @return global, center y coordinate
			 */
					double 	getGlobalY();	
		//@}


		/** 
		 * @name Rotation
		 */
		//@{
		public:
			/** 
			 * Gets rotation.
			 */
			double 	getRotation();
			/**
			 * Sets rotation.
			 */
			void 	setRotation(double r);
		//@}
			

		/** 
		 * @name Rotation
		 */
		//@{	
			/**
			 * Gets horizontal scale.
			 */
			double 	getScaleX();
			/**
			 * Sets horizontal scale.
			 */
			void 	setScaleX(double s);
			
			/**
			 * Gets vertical scale.
			 */
			double 	getScaleY();
			/**
			 * Gets vertical scale.
			 */
			void 	setScaleY(double s);
		//@}
			
	protected:

		/***********************************/
		/*         Member Variables        */
		/***********************************/
			// Object ID
			DisplayObjectIDType objid;
			
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
			
			int centerx;
			int centery;	

			// recalc centerx, centery
			virtual void calcCenterX();	
			virtual void calcCenterY();	
	
			double left;
			double bottom;
		
		/***********************************/
		/*         Member Functions        */
		/***********************************/
			// Virtual Constructor Implementation
			// Subclasses will 
			//	1) implement a "create" function 
			//	2) override init function
			DisplayObject( const shared_ptr<DisplayObject>& p, int x, int y, unsigned int w, unsigned int h, double r=0.0, double s=1.0, float o=1.0);
			
	private:
		static DisplayObjectIDType nextObjectID;
		
	};

}

#endif
