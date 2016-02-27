#include "GameTimer.h"

GameTimer::GameTimer(void)
{
	textColor.r = 0; textColor.g = 0; textColor.b = 0; textColor.a = 255;

	Renderer = NULL;
	textTexture = NULL;
	textSurface = NULL;
	textFont = NULL;

	timeText.str("");

	menuTime = 0;
	gameTime = 0;

}

void GameTimer::load(SDL_Renderer* renderer, TTF_Font* font)
{
	Renderer = renderer;
	textFont = font;
}

void GameTimer::render()
{
	gameTime = SDL_GetTicks() - menuTime;
	
	timeText<<"Time: "<<gameTime / 1000;

	textSurface = TTF_RenderText_Solid(textFont, timeText.str().c_str(), textColor);

	if(textSurface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);

		if(textTexture == NULL)
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textRect = textSurface->clip_rect;
			textRect.x = 1000 - (textSurface->w + 10);

			SDL_RenderCopy(Renderer, textTexture, NULL, &textRect);

			SDL_DestroyTexture(textTexture);
			SDL_FreeSurface(textSurface);

			textTexture = NULL;
			textSurface = NULL;
		}
	}
}

void GameTimer::startGameTime()
{
	gameTime = SDL_GetTicks() - menuTime;
}

void GameTimer::startMenuTime()
{
	menuTime = SDL_GetTicks();
}

Uint32 GameTimer::getGameTime()
{
	return gameTime;
}

void GameTimer::free()
{
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);

	textTexture = NULL;
	textSurface = NULL;

	TTF_CloseFont(textFont);
	textFont = NULL;
}

GameTimer::~GameTimer(void)
{
	free();
}
