#include "Finish.h"

Finish::Finish(void)
{
	finishRect.x = 0;
	finishRect.y = 0;
	finishRect.w = WIDTH;
	finishRect.h = HEIGHT;

	Renderer = NULL;
	finishTexture = NULL;
}

void Finish::load(int Xpos, int Ypos, SDL_Surface* finishsurface, SDL_Renderer* render)
{
	finishRect.x = Xpos;
	finishRect.y = Ypos;

	Renderer = render;

	finishTexture = SDL_CreateTextureFromSurface(render, finishsurface);

	if(finishTexture == NULL)
	{
		printf("unable to get finish, SDL error %s\n", SDL_GetError());
	}

	SDL_FreeSurface(finishsurface);
	finishsurface = NULL;
}

void Finish::render()
{
	SDL_RenderCopy(Renderer, finishTexture, NULL, &finishRect);
}

void Finish::free()
{
	SDL_DestroyTexture(finishTexture);
	finishTexture = NULL;
}

Finish::~Finish(void)
{
	free();
}