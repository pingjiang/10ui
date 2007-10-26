#include "SDL.h" 
#include "SDL_image.h"
#include <string>


SDL_Surface *load_image( std::string filename ) {
	return load_image(filename.c_str());
}
SDL_Surface *load_image( char *filename ) 
{
    // temporary storage for the image thats loaded
    SDL_Surface* loadedImage = NULL;
    
    // the optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    // load the image
	 loadedImage = IMG_Load(filename);
    
    // if nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        // create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        // free the old image
        SDL_FreeSurface( loadedImage );
    }
    
    // return the optimized image
    return optimizedImage;
}


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    // make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    // give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    // blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}