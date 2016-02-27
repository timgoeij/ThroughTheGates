#include "Gate.h"


Gate::Gate(void)
{
	gateRect.x = 0;
	gateRect.y = 0;
	gateRect.w = WIDTH;
	gateRect.h = HEIGHT;

	frame = 0;
	Framerate = 0;

	up = false;

	gateRects[0].x = 0; gateRects[0].y = 0; gateRects[0].w = 200; gateRects[0].h = 180;
	gateRects[1].x = 200; gateRects[1].y = 0; gateRects[1].w = 200; gateRects[1].h = 180;
	gateRects[2].x = 400; gateRects[2].y = 0; gateRects[2].w = 200; gateRects[2].h = 180;
	gateRects[3].x = 600; gateRects[3].y = 0; gateRects[3].w = 200; gateRects[3].h = 180;
	gateRects[4].x = 800; gateRects[4].y = 0; gateRects[4].w = 200; gateRects[4].h = 180;
	gateRects[5].x = 0; gateRects[5].y = 180; gateRects[5].w = 200; gateRects[5].h = 180;
	gateRects[6].x = 200; gateRects[6].y = 180; gateRects[6].w = 200; gateRects[6].h = 180;

	gate = NULL;
	Renderer = NULL;
}

void Gate::load(int Xpos, int Ypos, int startframe, double framerate, SDL_Surface* gatesurface, SDL_Renderer* renderer)
{
	gateRect.x = Xpos;
	gateRect.y = Ypos;

	frame = startframe;
	Framerate = framerate;

	Renderer = renderer;

	gate = SDL_CreateTextureFromSurface(renderer, gatesurface);

	if(gate == NULL)
	{
		printf("unable to get gate sdl error: %s\n", SDL_GetError());
	}
}

void Gate::render()
{
	SDL_Rect currentRect = gateRects[(int)frame / 7];
	SDL_RenderCopy(Renderer, gate, &currentRect, &gateRect);

	if(up)
	{
		frame -= Framerate;
		
		if(frame <= 0)
		{
			frame = 0;
			up = false;
		}
	}
	else
	{
		frame += Framerate;

		if(frame / 7 >= ANIMATION_FRAMES)
		{
			frame = 42;
			up = true;
		}
	}
}

void Gate::free()
{
	SDL_DestroyTexture(gate);
	gate = NULL;
}

int Gate::getFrame() const
{
	return (int)frame / 7;
}

Gate::~Gate(void)
{
	free();
}
