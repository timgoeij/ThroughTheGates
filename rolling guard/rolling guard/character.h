#include <sdl\SDL.h>
#include <stdio.h>

class character
{
public:
	character(void);
	
	void move(void);
	void render(void);
	
	void handlekeys(SDL_Event& keyEvent);
	void load(int Xpos, int Ypos, SDL_Surface* wheelsurface, SDL_Surface* charactersurface, SDL_Renderer* render);
	void free(void);
	
	bool walkright;
	bool walkleft;
	bool gravity;
	bool reset;

	SDL_Rect wheelRect;

	~character(void);

private:
	static const int WIDTH = 100;
	static const int HEIGHT = 100;
	static const int ANIMATION_FRAMES = 5;

	SDL_Texture* wheel;
	SDL_Texture* stickcharacter;

	SDL_Rect walkRects[ANIMATION_FRAMES];
	SDL_Rect idleRects[ANIMATION_FRAMES];

	SDL_Renderer* Renderer;

	int xvel, yvel, acceleration;
	int resetX, resetY;

	double degrees, frame;
	bool walk;

	void resetPos(void);
};

