#include "platform.h"

platform::platform(void)
{
	platformRect.x = 0;
	platformRect.y = 0;
	platformRect.w = WIDTH;
	platformRect.h = HEIGHT;

	Renderer = NULL;
	platformTexture = NULL;
}

void platform::load(int Xpos, int Ypos, SDL_Surface* platformsurface, SDL_Renderer* render)
{
	platformRect.x = Xpos;
	platformRect.y = Ypos;

	Renderer = render;

	platformTexture = SDL_CreateTextureFromSurface(Renderer, platformsurface);

	if(platformTexture == NULL)
	{
		printf("unable to get platform sdl error: %s\n", SDL_GetError());
	}
}

void platform::render()
{
	SDL_RenderCopy(Renderer, platformTexture, NULL, &platformRect);
}

void platform::free()
{
	SDL_DestroyTexture(platformTexture);
	platformTexture = NULL;
}

platform::~platform(void)
{
	free();
}
