#include "wal.h"

wal::wal(void)
{
	walRect.x = 0;
	walRect.y = 0;
	walRect.h = HEIGHT;
	walRect.w = WIDTH;

	Renderer = NULL;
	Wall = NULL;
}

void wal::load(int Xpos, int Ypos, SDL_Surface* wall, SDL_Renderer* render)
{
	walRect.x = Xpos;
	walRect.y = Ypos;

	Renderer = render;

	Wall = SDL_CreateTextureFromSurface(Renderer, wall);

	if(Wall == NULL)
	{
		printf("unable to get wal sdl error: %s\n", SDL_GetError());
	}
}

void wal::render()
{
	SDL_RenderCopy(Renderer, Wall, NULL, &walRect);
}

void wal::free()
{
	SDL_DestroyTexture(Wall);
	Wall = NULL;
}

wal::~wal(void)
{
	free();
}
