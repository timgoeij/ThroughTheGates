#include <sdl\SDL.h>
#include <stdio.h>

class platform
{
public:
	platform(void);

	void load(int Xpos, int Ypos, SDL_Surface* platformsurface, SDL_Renderer* render);
	void render(void);
	void free(void);

	SDL_Rect platformRect;

	~platform(void);

private:
	static const int WIDTH = 750;
	static const int HEIGHT = 10;

	SDL_Texture* platformTexture;
	SDL_Renderer* Renderer;
};

