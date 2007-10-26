#include "OpenGL_Graphics.h"

#include <iostream>
#include <math.h>

using namespace std;

namespace TenUI{
	/******************************/
	/*  Singleton Implementation  */
	/******************************/ 
	OpenGL_Graphics* OpenGL_Graphics::inst = NULL;		
	OpenGL_Graphics* OpenGL_Graphics::instance(){
		if(inst == NULL){
			inst = new OpenGL_Graphics();
		}
		return inst;
	}
		
	/******************************/
	/*  IGraphics Implementation  */
	/******************************/
		// Constants
		const float OpenGL_Graphics::PI = 3.14159265;
	
		// Helper Methods
		void OpenGL_Graphics::arcVertices(int x, int y, int radius, float a1, float a2, int resolution){
			if (a2 < a1){
				float t = a1;
			  	a1 = a2;
				a2 = t;
			}
			float step = (a2 - a1) / ((float)resolution);

			//cout << "x,y: " << x << "," << y << " radius,a1,a2,step: " << radius << ","<< a1 << ","<< a2 << ","<< step << endl; 
			for (double d = a1; d <= a2; d += step){
				int vx = (int) (cos(d) * radius + x + 0.5);
				int vy = (int) (sin(d) * radius + y + 0.5);

				cout << "vx,vy: " << vx << "," << vy << endl;
				glVertex2i((int) (cos(d) * radius + x + 0.5), (int) (sin(d) * radius + y + 0.5));
			}

			cout << "vx,vy: " << x << "," << y << endl;
			glVertex2i(x,y);

			int vx = (int) (cos(a1) * radius + x + 0.5);
			int vy = (int) (sin(a1) * radius + y + 0.5);
			cout << "vx,vy: " << vx << "," << vy << endl;
			glVertex2i((int) (cos(a1) * radius + x + 0.5), (int) (sin(a1) * radius + y + 0.5));
			cout << endl;
			cout << endl;
		}
		
		
		void OpenGL_Graphics::init(GraphicsOptions* graphicsOptions) throw(IGraphicsEnums::IGRAPHICS_EXCEPTION) {
			this->graphicsOptions = graphicsOptions;
			
			cout << "OpenGL_Graphics::init { "
				 << graphicsOptions->getWidth() << ", "
				 << graphicsOptions->getHeight() << ", "
				 << graphicsOptions->getBPP() << ", "
				 << graphicsOptions->getScreenMode() << ", "
				 << graphicsOptions->getFontsDirectory() << " }" << endl;
			
			/**********************/
			/*      INIT SDL      */
			/**********************/
				if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
					throw IGraphicsEnums::INIT_FAILED;
					return;
				}		
								
				if ( SDL_SetVideoMode(  graphicsOptions->getWidth(), 
										graphicsOptions->getHeight(), 
										graphicsOptions->getBPP(), 
										SDL_OPENGL | ((graphicsOptions->getScreenMode() == IGraphicsEnums::FULLSCREEN)?SDL_FULLSCREEN:0) ) == NULL ) { 
					SDL_Quit();
					throw IGraphicsEnums::INIT_FAILED;
					return;
				}
				//SDL_WM_SetCaption(app->getName(), NULL);
				
			/**********************/
			/*     INIT OpenGL    */
			/**********************/
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
		
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
				
				glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
				glClearDepth(1.0f);									// Depth Buffer Setup
				glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations		
		
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0);					// Full Brightness.  50% Alpha
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);	// Set The Blending Function For Translucency	
				
				glEnable (GL_LINE_SMOOTH);		
	
			/**********************/
			/*     INIT Fonts     */
			/**********************/
				this->fontMgr = FontManager_FT2::createInstance(graphicsOptions->getFontsDirectory());
			

			/**********************/
			/*   Color Selection  */
			/**********************/
				int redBits, greenBits, blueBits;
				glGetIntegerv( GL_RED_BITS, &redBits );
				glGetIntegerv( GL_GREEN_BITS, &greenBits );
				glGetIntegerv( GL_BLUE_BITS, &blueBits );
				redSelMask 		= bitMask(redBits)   << (greenBits + blueBits);
				greenSelMask 	= bitMask(greenBits) << blueBits;
				blueSelMask 	= bitMask(blueBits);
				redSelShift 	= 32 - (redBits+greenBits+blueBits);
				greenSelShift 	= 32 - (greenBits+blueBits);
				blueSelShift 	= 32 -  blueBits;	
		}
		void OpenGL_Graphics::deinit(){
			delete fontMgr;
			
			vector<OpenGL_Image *>::iterator it = images.begin();
			while(it != images.end()){
				(*it)->freeTexture();
			}
	
			SDL_Quit();
		}
		string OpenGL_Graphics::getImplName(){ return string("OpenGL_Graphics"); }
	
		GraphicsOptions& OpenGL_Graphics::getGraphicsOptions(){ return (*graphicsOptions); }
		
			/******************************/
			/*       Viewport Methods     */
			/******************************/ 
				void 	OpenGL_Graphics::pushViewTransformation(int x, int y, float rotation, float scalex, float scaley){
					glPushMatrix();	
					
					// translate, rotate, scale
					glTranslatef((GLdouble)x,(GLdouble)y,0);
					glRotatef((GLfloat)rotation,0,0,1);
					glScalef((GLfloat)scalex,(GLfloat)scaley,1.0);
				}
				void 	OpenGL_Graphics::popViewTransformation(){
					glPopMatrix();
				}
				
				void 	OpenGL_Graphics::setClipping(int x, int y, int width, int height){
					glEnable(GL_SCISSOR_TEST);
					glScissor(x,y, width, height);
				}
				void 	OpenGL_Graphics::resetClipping(){
					glDisable(GL_SCISSOR_TEST);
				}
				Rect 	OpenGL_Graphics::getClipping(){
					GLint rect[4];
					glGetIntegerv( GL_SCISSOR_BOX, rect );
					return Rect((int)rect[0], (int)rect[1], (int)rect[2], (int)rect[3]);
				}
	
			/*******************************/
			/*      Rendering Methods      */
			/*******************************/
				void  	OpenGL_Graphics::beginRendering(IGraphicsEnums::IGRAPHICS_RENDERING_MODE mode){
					renderMode = mode;
					
					int vPort[4];
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					glGetIntegerv(GL_VIEWPORT, vPort);
					
					glMatrixMode(GL_PROJECTION);
					glPushMatrix();
					glLoadIdentity();
					
					glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();
					glLoadIdentity();
				}
				void  	OpenGL_Graphics::endRendering(){
					SDL_GL_SwapBuffers();					
					glMatrixMode(GL_PROJECTION);
					glPopMatrix();   
					glMatrixMode(GL_MODELVIEW);
					glPopMatrix();	
				}
			
			/*******************************/
			/* Selection Rendering Methods */
			/*******************************/
				void  			OpenGL_Graphics::setColorID(unsigned long id){
					glColor3ui (id & redSelMask << redSelShift, 
								id & greenSelMask << greenSelShift, 
								id & blueSelMask << blueSelShift);						
				}
				unsigned long  	OpenGL_Graphics::getColorID(int x, int y){}		
											
			/******************************/
			/*    Geometry Draw Methods   */
			/******************************/ 
				void  	OpenGL_Graphics::drawLine(int x1, int y1, int x2, int y2, int strokeSize, const ColorHex& color){
					setColor(color);
					glLineWidth(strokeSize);

					// draw line
					glBegin(GL_LINES);				
						glVertex2i(x1,y1);
						glVertex2i(x2,y2);					
					glEnd();
				}		
			
					/******************************/
					/*   Rectangle Draw Methods   */
					/******************************/
						void 	OpenGL_Graphics::drawRectangle(	int x, int y, 
													int width, int height, 
													const ColorHex& color, 
													int strokeSize, const ColorHex& strokeColor){
							if(strokeSize>0){
							// rectangle's stroke
								setColor(strokeColor);
							
							// draw line
								glBegin(GL_QUADS);	            						
									glVertex2i( x-strokeSize 		,y-strokeSize		 );
									glVertex2i( x-strokeSize 		,y+height+strokeSize );
									glVertex2i( x+width+strokeSize	,y+height+strokeSize );
									glVertex2i( x+width+strokeSize	,y-strokeSize		 );
								glEnd();
							}
							
							// rectangle's color
								setColor(color);
								
							// draw rectangle
								glBegin(GL_QUADS);
									glVertex2i( x		,y	 	  );
									glVertex2i( x		,y+height );
									glVertex2i( x+width	,y+height );
									glVertex2i( x+width	,y	      );
								glEnd();
						}
						void  	OpenGL_Graphics::drawGradientRect(	int x, int y, 
														int width, int height, 
														const ColorHex& lb, const ColorHex& lt, const ColorHex& rt, const ColorHex& rb, 
														int strokeSize, const ColorHex& strokeColor ){

							if(strokeSize>0){
							// rectangle's stroke
								setColor(strokeColor);
							
							// draw line
								glBegin(GL_QUADS);	            						
									glVertex2i( x-strokeSize 		,y-strokeSize		 );
									glVertex2i( x-strokeSize 		,y+height+strokeSize );
									glVertex2i( x+width+strokeSize	,y+height+strokeSize );
									glVertex2i( x+width+strokeSize	,y-strokeSize		 );
								glEnd();
							}
								
							// draw rectangle
								glBegin(GL_QUADS);
									setColor(lb);
									glVertex2i( x		,y	 	  );
									setColor(lt);
									glVertex2i( x		,y+height );									
									setColor(rt);
									glVertex2i( x+width	,y+height );
									setColor(rb);
									glVertex2i( x+width	,y	 	  );
								glEnd();
						}
						void  	OpenGL_Graphics::drawRoundedRectangle(	int x, int y, 
															int width, int height, int radius, 
															const ColorHex& color, 
															int strokeSize, const ColorHex& strokeColor ){	
							
							cout << "drawRoundedRectangle" << endl;
							float top = PI * 0.5f;
							float right = 0.0f;
							float bottom = PI * 1.5f;
							float left = PI;

							setColor(color);

							glLineWidth(3);
														
							// draw rectangle
							glBegin(GL_POLYGON);
								/*glVertex2i( x		,y	 	  );
								glVertex2i( x		,y+height );
								glVertex2i( x+width	,y+height );
								glVertex2i( x+width	,y	      );
								glVertex2i( x		,y	 	  );*/

							glVertex2i( 25,100 );
							glVertex2i( 15,98 );
							glVertex2i( 7,93 );
							glVertex2i( 2,85 );
							glVertex2i( 0,75 );
							glVertex2i( 25,75 );
							glVertex2i( 25,100 );
							
								//glVertex2i( x,y	);
								//arcVertices(x+radius, y+height-radius, radius, left, top);
							glEnd();

							/*glBegin(GL_POLYGON);	
								arcVertices(x+width-radius, y+height-radius, radius, top, right);
							glEnd();

							glBegin(GL_POLYGON);	
								arcVertices(x+width-radius, y+radius, radius, right, bottom);
							glEnd();

							glBegin(GL_POLYGON);	
								arcVertices(x+radius, y+radius, radius, bottom, left);
							glEnd();*/							
						}
						void  	OpenGL_Graphics::drawGradientRoundedRect(	int x, int y, 
																int width, int height, int radius, 
																const ColorHex& c1, const ColorHex& c2, const ColorHex& c3, const ColorHex& c4,
																int strokeSize, const ColorHex& strokeColor ){
							
						}
			
					/******************************/
					/*     Circle Draw Methods    */
					/******************************/
						void  	OpenGL_Graphics::drawRoundedCorner(	int x, int y, 
														double a1, double a2, 
														double radius, int resolution,
														const ColorHex& fillColor,
														int strokeSize, const ColorHex& strokeColor ){
							
						}
						
				/******************************/
				/*         Image Methods      */
				/******************************/ 
					//TODO Try default argument based on another argument
					void OpenGL_Graphics::drawImage(const IImage* img, 
													int x, int y, 
													float opacity,
													unsigned int width, unsigned int height){
						OpenGL_Image* openglImage = (OpenGL_Image*) img;
						if(height==0){
							height = openglImage->getImageHeight();
						}
						if(width==0){
							width = openglImage->getImageWidth();
						}
									
						
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, openglImage->getTextureID());
			
						
						// draw rectangle
						glBegin(GL_QUADS);		                
							glTexCoord2i(0,0); glVertex2d(x,y);
							glTexCoord2i(0,1); glVertex2d(x,y+height);
							glTexCoord2i(1,1); glVertex2d(x+width,y+height);
							glTexCoord2i(1,0); glVertex2d(x+width,y);
						glEnd();
						
						glBindTexture(GL_TEXTURE_2D, 0);
						glDisable(GL_TEXTURE_2D);			
					}
					const IImage* OpenGL_Graphics::loadImage(const string& imageFile){
						return OpenGL_Image::loadFromFile(imageFile);
					}
			
				/******************************/
				/*         Text Methods       */
				/******************************/
					void  	OpenGL_Graphics::drawText(const string& text, int x, int y, const ColorHex& color){}
					void  	OpenGL_Graphics::loadFontDir(const string &fontdir){}
										
					void 	OpenGL_Graphics::setColor(float red, float green, float blue, float alpha){
						if(renderMode == IGraphicsEnums::DISPLAY) { 
							glColor4f(red,green,blue,alpha); 
						}
					}	
					void 	OpenGL_Graphics::setColor(const ColorHex& ch){
						if(renderMode == IGraphicsEnums::DISPLAY) { 
							glColor4f(ch.getRed(),ch.getBlue(),ch.getGreen(),ch.getAlpha()); 
						}
					}
			
}
