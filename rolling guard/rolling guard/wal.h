#include <sdl\SDL.h>
#include <stdio.h>

class wal
{
public:
	wal(void);
	
	void load(int Xpos, int Ypos, SDL_Surface* wall, SDL_Renderer* render);
	void render(void);
	void free(void);

	SDL_Rect walRect;

	~wal(void);

private:
	static const int WIDTH = 10;
	static const int HEIGHT = 800;

	SDL_Texture* Wall;
	SDL_Renderer* Renderer;
};

