#include <sdl\SDL.h>
#include <stdio.h>

class Gate
{
public:
	Gate(void);

	void load(int Xpos, int Ypos, int startframe, double framerate, SDL_Surface* gatesurface, SDL_Renderer* renderer);
	void render(void);
	void free(void);

	SDL_Rect gateRect;

	int getFrame(void) const;

	~Gate(void);

private:
	static const int WIDTH = 200;
	static const int HEIGHT = 180;

	static const int ANIMATION_FRAMES = 7;

	SDL_Rect gateRects[ANIMATION_FRAMES];

	SDL_Texture* gate;
	SDL_Renderer* Renderer;

	double Framerate;
	double frame;

	bool up;

};

