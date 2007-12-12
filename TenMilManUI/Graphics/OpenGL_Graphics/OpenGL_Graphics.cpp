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
			float step = (a2 - a1) / ((float)resolution);
			
			if( a2<a1 ){
				for (double d = a1; d >= a2; d += step){
					glVertex2i((int) (cos(d) * radius + x + 0.5), (int) (sin(d) * radius + y + 0.5));
				}	
			}else{
				for (double d = a1; d <= a2; d += step){
					glVertex2i((int) (cos(d) * radius + x + 0.5), (int) (sin(d) * radius + y + 0.5));
				}
			}
		}
		char *OpenGL_Graphics::int2bin(int a){
			 char *str,*tmp;
			 int cnt = 31;
			 str = (char *) malloc(33); /*32 + 1 , becoz its a 32 bit bin number*/
			 tmp = str;
			 while ( cnt > -1 ){
			      str[cnt]= '0';
			      cnt --;
			 }
			 cnt = 31;
			 while (a > 0){
			       if (a%2==1){
			           str[cnt] = '1';
			        }
			      cnt--;
			        a = a/2 ;
			 }
			 tmp[32] = 0;
			 return tmp;   

		} 
		
		char *OpenGL_Graphics::byte2bin(unsigned char a){
			 char *str;
			 int cnt = 7;
			 str = (char *) malloc(9);
			 for(int i=0; i<8; ++i){ str[i] = '0'; }
			 while (a > 0){
				 str[cnt] = (a%2==1)?'1':'0';
			     
			     cnt--;
			     a = a/2 ;
			 }
			 str[8] = 0;
			 return str;
		} 
		
		
		void OpenGL_Graphics::init(GraphicsOptions* graphicsOptions) throw(IGraphicsEnums::IGRAPHICS_EXCEPTION) {
			this->graphicsOptions = graphicsOptions;
			
			cout << "TenUI/Graphics/OpenGL_Graphics::init { "
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
										SDL_OPENGL | SDL_HWSURFACE | ((graphicsOptions->getScreenMode() == IGraphicsEnums::FULLSCREEN)?SDL_FULLSCREEN:0) ) == NULL ) { 
					SDL_Quit();
					throw IGraphicsEnums::INIT_FAILED;
					return;
				}
				SDL_WM_SetCaption(graphicsOptions->getWindowTitle().c_str(), NULL);
				
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

				//glBlendFunc(GL_SRC_COLOR,GL_DST_COLOR);	
				//glEnable (GL_POLYGON_SMOOTH);		
	
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
				greenSelMask 	= bitMask(greenBits) << (blueBits);
				blueSelMask 	= bitMask(blueBits);
				
				blueSelShift 	= 24 - (redBits+greenBits+blueBits);
				greenSelShift 	= 24 - (redBits+greenBits);
				redSelShift 	= 24 - (redBits);
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
					if( renderMode == IGraphicsEnums::DISPLAY ){
						SDL_GL_SwapBuffers();					
					}
					glMatrixMode(GL_PROJECTION);
					glPopMatrix();   
					glMatrixMode(GL_MODELVIEW);
					glPopMatrix();	
				}
				IGraphicsEnums::IGRAPHICS_RENDERING_MODE OpenGL_Graphics::getRenderingMode(){
					return renderMode;
				}
			
			/*******************************/
			/* Selection Rendering Methods */
			/*******************************/
				void  			OpenGL_Graphics::setColorID(unsigned long id){
					GLubyte pixel[3];
					
					pixel[0] = (GLubyte) ((id & redSelMask)  >> redSelShift);
					pixel[1] = (GLubyte) ((id & greenSelMask)>> greenSelShift);
					pixel[2] = (GLubyte) ((id & blueSelMask) >> blueSelShift);
							
					glColor3ub (pixel[0], 
								pixel[1], 
								pixel[2]);					
				}
				unsigned long  	OpenGL_Graphics::getColorID(int x, int y){					
					GLubyte	pixel[3];
					glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
				        				      									      
					unsigned long id = 	(((unsigned long)pixel[0] << redSelShift) ) 	|
										(((unsigned long)pixel[1] << greenSelShift) ) 	|
					  					(((unsigned long)pixel[2] << blueSelShift) );
					return id;
				}
											
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
							float top = PI * 0.5f;
							float right = PI *2.0f;
							float bottom = PI * 1.5f;														
							float left = PI;

							// draw rounded rectangle's stroke
							setColor(strokeColor);
							
							// draw rectangle
							glBegin(GL_POLYGON);								
								arcVertices(x+width-radius, y+radius, 			radius+strokeSize, right, bottom);
								arcVertices(x+radius, 		y+radius, 			radius+strokeSize, bottom,left);
								arcVertices(x+radius, 		y+height-radius, 	radius+strokeSize, left, 	top);
								arcVertices(x+width-radius,	y+height-radius, 	radius+strokeSize, top, 0.0);
							glEnd();
							
							setColor(color);
							
							// draw rectangle
							glBegin(GL_POLYGON);								
								arcVertices(x+width-radius, y+radius, 			radius, right, bottom);
								arcVertices(x+radius, 		y+radius, 			radius, bottom,left);
								arcVertices(x+radius, 		y+height-radius, 	radius, left, 	top);
								arcVertices(x+width-radius,	y+height-radius, 	radius, top, 0.0);
							glEnd();
							
						}
						//TODO Implement OpenGL_Graphics::drawGradientRoundedRect
						void  	OpenGL_Graphics::drawGradientRoundedRect(	int x, int y, 
																int width, int height, int radius, 
																const ColorHex& lb, const ColorHex& lt, const ColorHex& rt, const ColorHex& rb,
																int strokeSize, const ColorHex& strokeColor ){
							float top = PI * 0.5f;
							float right = PI *2.0f;
							float bottom = PI * 1.5f;														
							float left = PI;

							// draw rounded rectangle's stroke
							setColor(strokeColor);
							
							// draw rectangle
							glBegin(GL_POLYGON);								
								arcVertices(x+width-radius, y+radius, 			radius+strokeSize, right, bottom);
								arcVertices(x+radius, 		y+radius, 			radius+strokeSize, bottom,left);
								arcVertices(x+radius, 		y+height-radius, 	radius+strokeSize, left, 	top);
								arcVertices(x+width-radius,	y+height-radius, 	radius+strokeSize, top, 0.0);
							glEnd();
														
							// draw rectangle
							glBegin(GL_POLYGON);
								setColor(rb);
								arcVertices(x+width-radius, y+radius, 			radius, right, bottom);
								setColor(lb);
								arcVertices(x+radius, 		y+radius, 			radius, bottom,left);
								setColor(lt);
								arcVertices(x+radius, 		y+height-radius, 	radius, left, 	top);
								setColor(rt);
								arcVertices(x+width-radius,	y+height-radius, 	radius, top, 0.0);
							glEnd();
						}
			
					/******************************/
					/*     Circle Draw Methods    */
					/******************************/
						void  	OpenGL_Graphics::drawRoundedCorner(	int x, int y, 
														double a1, double a2, 
														double radius, int resolution,
														const ColorHex& fillColor,
														int strokeSize, const ColorHex& strokeColor ){}
						
				/******************************/
				/*         Image Methods      */
				/******************************/ 
					//TODO Try default argument based on another argument
					void OpenGL_Graphics::drawImage(const IImage* img, 
													int x, int y, 
													float opacity,
													unsigned int width, unsigned int height){
						if(img != 0){
							OpenGL_Image* openglImage = (OpenGL_Image*) img;
							if(height==0){
								height = (renderMode == IGraphicsEnums::DISPLAY)?openglImage->getTextureHeight():openglImage->getImageHeight();
							}else{
								if(renderMode == IGraphicsEnums::DISPLAY){
									height = (height/openglImage->getImageHeight())*openglImage->getTextureHeight();
								}
							}
							if(width==0){
								width = (renderMode == IGraphicsEnums::DISPLAY)?openglImage->getTextureWidth():openglImage->getImageWidth();
							}else{
								if(renderMode == IGraphicsEnums::DISPLAY){
									width = (width/openglImage->getImageWidth())*openglImage->getTextureWidth();
								}
							}
							
							setColor(1.0,1.0,1.0,opacity);
							
							if(renderMode == IGraphicsEnums::DISPLAY) { 
								glEnable(GL_TEXTURE_2D);
								glBindTexture(GL_TEXTURE_2D, openglImage->getTextureID());
							}
								// draw rectangle
								glBegin(GL_QUADS);		                
									glTexCoord2i(0,0); glVertex2d(x,y);
									glTexCoord2i(0,1); glVertex2d(x,y+height);
									glTexCoord2i(1,1); glVertex2d(x+width,y+height);
									glTexCoord2i(1,0); glVertex2d(x+width,y);
								glEnd();
	
							if(renderMode == IGraphicsEnums::DISPLAY) { 
								glBindTexture(GL_TEXTURE_2D, 0);
								glDisable(GL_TEXTURE_2D);		
							}
						}
					}
					IImage* OpenGL_Graphics::loadImage(const string& imageFile){
						return OpenGL_Image::loadFromFile(imageFile);
					}
			
				/******************************/
				/*         Text Methods       */
				/******************************/
					void  	OpenGL_Graphics::drawText(const string& text, const string& fontKey,int fontSize, int x, int y, const ColorHex& color){
						glColor4d(color.getRed(),color.getGreen(),color.getBlue(),color.getAlpha());
						fontMgr->render(fontKey,FontFamilyData::DEFAULT, fontSize, "%s",text.c_str());
					}
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
