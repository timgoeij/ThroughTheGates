#include <sdl\SDL.h>
#include <stdio.h>

class Finish
{
public:
	Finish(void);

	void load(int Xpos, int Ypos, SDL_Surface* finishsurface, SDL_Renderer* render);
	void render(void);
	void free(void);

	SDL_Rect finishRect;

	~Finish(void);

private:
	static const int WIDTH = 100;
	static const int HEIGHT = 100;

	SDL_Texture* finishTexture;
	SDL_Renderer* Renderer;

};

