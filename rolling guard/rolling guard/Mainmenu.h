#include <sdl\SDL.h>
#include <sdl\SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
class Mainmenu
{
public:
	Mainmenu(void);
	
	void load(SDL_Surface* menuSurface, SDL_Surface* helpSurface, TTF_Font* font, SDL_Renderer* render);

	void handlemouse(SDL_Event& mouseEvent);
	
	void render(void);

	void setFrame(int Frame);

	void setEndTime(Uint32 endTime);

	void free(void);

	bool active;
	bool quit;
	
	~Mainmenu(void);

private:
	static const int BUTTON_FRAMES = 2;
	static const int MENU_BUTTONS = 3;

	//source rects for the buttons
	SDL_Rect startButtons[BUTTON_FRAMES];
	SDL_Rect quitBackButtons[BUTTON_FRAMES];
	SDL_Rect helpButtons[BUTTON_FRAMES];
	
	//source rect for title and endtitle
	SDL_Rect titleRect;
	SDL_Rect endTitleRect;
	SDL_Rect helpRect;

	//destination rects
	SDL_Rect buttons[MENU_BUTTONS];
	SDL_Rect title;
	SDL_Rect help;
	SDL_Rect timeRect;

	bool selected[MENU_BUTTONS];
	bool select;

	//the endtime from the player
	Uint32 EndTime;

	//the text font in the game
	TTF_Font* textFont;

	//the color form the text
	SDL_Color textColor;

	int MouseX, MouseY, frame;
	
	SDL_Texture* menuTexture;
	SDL_Texture* helpTexture;
	SDL_Texture* timeTexture;

	SDL_Renderer* Renderer;
};

