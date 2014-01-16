#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <stdio.h>

#define NEGRE 0x000000ff
#define R(x) (int) round(x)

void dibuixaFractal(SDL_Surface* screen, double x, double y, double w, double h, double midamin);
int procEvents(SDL_Surface* screen);

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 1024x768 video: %s\n", SDL_GetError());
        return 1;
    }

    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
     
    // fem el fractal
    if(argc==2)
		dibuixaFractal(screen, 10, 590, 670, 580, atoi(argv[1]));
	else
		dibuixaFractal(screen, 10, 590, 670, 580, 15);
    
    while(procEvents(screen));
    printf("Exited cleanly\n");
    return 0;
}

int procEvents(SDL_Surface* screen)
{
	static SDL_Event event;
	static Uint8* keystate;
	
	keystate = SDL_GetKeyState(NULL);
	
	
	while (SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			exit(0);
			return 0;
		}
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_ESCAPE)
			exit(0);
			return 0;
		}
	}
	SDL_Flip(screen);
	return 1;
}


void dibuixaFractal(SDL_Surface* screen, double x, double y, double w, double h, double midamin)
{
	trigonColor(screen, R(x), R(y), R(x+w), R(y), R(x+(w/2)), R(y-h), NEGRE);
	procEvents(screen);
	if(w<=midamin || h<=midamin)
		return;
	dibuixaFractal(screen, R(x), R(y), R(w/2), R(h/2), midamin);
	dibuixaFractal(screen, R(x+(w/4)), R(y-(h/2)), R(w/2), R(h/2), midamin);
	dibuixaFractal(screen, R(x+(w/2)), R(y), R(w/2), R(h/2), midamin);
	return;
}
