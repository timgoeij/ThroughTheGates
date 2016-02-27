#include <sdl\SDL.h>
#include <sdl\SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

class GameTimer
{
public:
	GameTimer(void);

	void load(SDL_Renderer* renderer, TTF_Font* font);
	void render();

	void startMenuTime(void);
	void startGameTime(void);

	Uint32 getGameTime(void);

	void free(void);

	~GameTimer(void);
private:

	SDL_Color textColor;

	SDL_Rect textRect;
	
	SDL_Renderer* Renderer;

	TTF_Font* textFont;

	SDL_Texture* textTexture;
	SDL_Surface* textSurface;

	std::stringstream timeText;
	
	Uint32 menuTime;
	Uint32 gameTime;
};

