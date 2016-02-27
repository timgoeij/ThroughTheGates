//Using SDL, SDL_image, standard IO, string, sstream, vector, character class, 
//wal class, platform class, Gate class, Finish class, Mainmenu class
#include <sdl\SDL.h>
#include <sdl\SDL_image.h>
#include <sdl\SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "character.h"
#include "wal.h"
#include "platform.h"
#include "Gate.h"
#include "Finish.h"
#include "Mainmenu.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

//The window renderer
SDL_Renderer* renderer = NULL;

//the text font in the game
TTF_Font* textFont = NULL;
	 
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//the Main menu in the game
Mainmenu menu;

//the character in the game
character Character;

//the finish flag in the game
Finish finish;

//the walls in the game
std::vector<wal> wallVector;

//the platforms in the game
std::vector<platform> platformVector;

//the gates in the game
std::vector<Gate> gatevector;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		
		//Create window
		gWindow = SDL_CreateWindow( "Through the gates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s/n",SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer,0,0,0,255);
				
				//initialize SDL_IMAGE
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//initialize SDL_TTF
				if(TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//initialize text font
	textFont = TTF_OpenFont("ttf/myriad-web-pro.ttf", 48);

	if(textFont == NULL)
	{
		 printf( "Failed to load myriad font! SDL_ttf Error: %s\n", TTF_GetError());
		 success = false;
	}

#pragma region initialize character
	//load the media for the character
	SDL_Surface* wheelsurface = IMG_Load("images/character_wheel.png");
	SDL_Surface* charactersurface = IMG_Load("images/character.png");

	if(wheelsurface == NULL || charactersurface == NULL)
	{
		printf("unable to get character %s\n",SDL_GetError());
	}

	Character.load(30, 0, wheelsurface, charactersurface, renderer);

#pragma endregion
#pragma region initialize finish flag
	//load the media for the finish flag
	SDL_Surface* finishsurface = IMG_Load("images/finish.png");

	if(finishsurface == NULL)
	{
		printf("unable to get finish flag %s\n",SDL_GetError());
	}
	
	finish.load(10, SCREEN_HEIGHT - finishsurface->h, finishsurface, renderer);
#pragma endregion
#pragma region initialize walls
	//load the media for the walls
	SDL_Surface* walsurface = IMG_Load("images/wal.png");

	if(walsurface == NULL)
	{
		printf("unable to get wal %s\n",SDL_GetError());
	}

	wal Wall;
	wallVector.push_back(Wall);
	wal Wall2;
	wallVector.push_back(Wall2);

	wallVector[0].load(0, 0, walsurface, renderer);
	wallVector[1].load(SCREEN_WIDTH - walsurface->w, 0, walsurface, renderer);

	SDL_FreeSurface(walsurface);
	walsurface = NULL;
#pragma endregion
#pragma region initialize platforms
	//load the media for the platforms
	SDL_Surface* platformsurface = IMG_Load("images/platform.png");

	if(platformsurface == NULL)
	{
		printf("unable to get platform %s\n", SDL_GetError());
	}

	platform Platform;
	platformVector.push_back(Platform);
	platform Platform2;
	platformVector.push_back(Platform2);
	platform Platform3;
	platformVector.push_back(Platform3);

	platformVector[0].load(0, 200, platformsurface, renderer);
	platformVector[1].load(SCREEN_WIDTH - platformsurface->w , 400, platformsurface, renderer);
	platformVector[2].load(0, 600, platformsurface, renderer);

	SDL_FreeSurface(platformsurface);
	platformsurface = NULL;

#pragma endregion
#pragma region initialize gates
	//load the media for the gates
	SDL_Surface* gatesurface = IMG_Load("images/gate.png");

	if(gatesurface == NULL)
	{
		printf("unable to get gate %s\n",SDL_GetError());
	}

	Gate gate;
	gatevector.push_back(gate);
	Gate gate2;
	gatevector.push_back(gate2);
	Gate gate3;
	gatevector.push_back(gate3);
	Gate gate4;
	gatevector.push_back(gate4);
	Gate gate5;
	gatevector.push_back(gate5);
	Gate gate6;
	gatevector.push_back(gate6);

	gatevector[0].load(200, 20, 0, 0.35, gatesurface, renderer);
	gatevector[1].load(550, 20, 7, 0.3, gatesurface, renderer);
	gatevector[2].load(300, 220, 14, 0.3, gatesurface, renderer);
	gatevector[3].load(300, 420, 21, 0.35, gatesurface, renderer);
	gatevector[4].load(200, SCREEN_HEIGHT - gatesurface->h / 2, 28, 0.3, gatesurface, renderer);
	gatevector[5].load(550, SCREEN_HEIGHT - gatesurface->h / 2 , 35, 0.35, gatesurface, renderer);
	
	SDL_FreeSurface(gatesurface);
#pragma endregion
#pragma region initialize menu
	//load the media for the menu
	SDL_Surface* menuSurface = IMG_Load("images/menu.png");
	SDL_Surface* helpSurface = IMG_Load("images/helpmenu.png");

	if(menuSurface == NULL)
	{
		printf("unable to get menu sdl error: %s", SDL_GetError());
	}

	if(helpSurface == NULL)
	{
		printf("unable to get helpmenu sdl error: %s", SDL_GetError());
	}

	menu.load(menuSurface, helpSurface,textFont, renderer);
#pragma endregion

	return success;
}

void close()
{
	//free textures from the character, finish and the menu
	Character.free();
	finish.free();
	menu.free();

	//free textures for al walls
	for(unsigned int walindex = 0; walindex < wallVector.size(); ++walindex)
	{
		wallVector[walindex].free();
	}

	//free textures for al platforms
	for(unsigned int platformindex = 0; platformindex < platformVector.size(); ++platformindex)
	{
		platformVector[platformindex].free();
	}

	//free textures for al gates
	for(unsigned int gateindex = 0; gateindex < gatevector.size(); ++gateindex)
	{
		gatevector[gateindex].free();
	}

	//Destroy window and renderer
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL and SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

int checkWalCollisions(SDL_Rect character, SDL_Rect wal)
{
	int charleft, walleft;
	int charright, walright;

	// get the bounds of the character
	charleft = character.x;
	charright = character.x + character.w;

	//get the bounds of the wal
	walleft = wal.x;
	walright = wal.x + wal.w;

	//collision right side of the character
	if(charright >= walleft && charright < walright)
	{
		return 1;
	}

	//collision left side of the character
	if(charleft <= walright && charleft > walleft)
	{
		return 2;
	}

	return 0;
}

bool checkPlatformCollisions(SDL_Rect character, SDL_Rect platform)
{
	int chartop, charbottom;
	int charleft, charright;
	int platformtop, platformbottom;
	int platformleft, platformright;

	//get the bounds of the character
	chartop = character.y;
	charbottom = character.y + character.h;
	charleft = character.x;
	charright = character.x + character.w;

	//get the bounds of the platforms
	platformtop = platform.y;
	platformbottom = platform.y + platform.h;
	platformleft = platform.x;
	platformright = platform.x + platform.w;

	//is there an collision between bottom from the character 
	//and the top from the platform
	if(charbottom >= platformtop && charbottom < platformbottom)
	{
		//is the left side and the right side between the bounds
		//from the platform
		if(charleft >= platformleft && charright <= platformright)
		{
			return true;
		}

		//is the left side from the character ouside the bounds from the platform
		//and right side from the character inside the bounds from the platform
		if(charleft <= platformleft && charright >= platformleft)
		{
			return true;
		}

		//is the left side from the character inside the bounds from the platform
		//and right side from the character outside the bounds from the platform
		if(charleft <= platformright && charright >= platformright)
		{
			return true;
		}

		return false;
	}

	return false;
}

bool checkGateCollisions(SDL_Rect character, SDL_Rect gate, int frame)
{
	int charleft, gateleft;
	int charright, gateright;
	int chartop, gatetop;
	int charbottom, gatebottom;

	// get the bounds of the character
	charleft = character.x;
	charright = character.x + character.w;
	chartop = character.y;
	charbottom = character.y + character.h;

	//get the bounds of the gate
	gateleft = gate.x;
	gateright = gate.x + gate.w; 
	gatetop = gate.y;
	gatebottom = gate.y + gate.h;

	//check for a collision on the right side or the left side of the character
	if((charright >= gateleft && charright < gateright) || (charleft <= gateright && charleft > gateleft))
	{
		//check of 
		if((chartop >= gatetop && chartop <= gatebottom) && (charbottom >= gatetop && charbottom <= gatebottom))
		{
			if(frame <= 3)
			{
				return true;
			}

			return false;
		}

		return false;
	}

	return false;
}

int wmain()
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//textcolor
			SDL_Color textColor = {0, 0, 0, 255};

			//the time in the menu
			Uint32 menuTime = 0;

			//the time in the game
			Uint32 gameTime = 0;

			//in memory text stream
			std::stringstream timeText;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					if(!menu.active)
					{
						Character.handlekeys(e);
					}
					else
					{
						menu.handlemouse(e);
					}
				}

				//while menu is active
				if(menu.active)
				{
					//clear the screen
					SDL_RenderClear(renderer);
					
					//render menu
					menu.render();

					//get the time in the menu 
					menuTime = SDL_GetTicks();

					//if player click the quit button
					if(menu.quit)
					{
						quit = true;
					}

					//update screen
					SDL_RenderPresent(renderer);
				}
				else
				{
					//move the character
					Character.move();

					//Clear screen
					SDL_RenderClear(renderer);

					//calculated the gametime and set the text to be rendered
					gameTime = (SDL_GetTicks() - menuTime) / 1000;
					timeText.str("");
					timeText<<"Time: "<<gameTime;

					SDL_Surface* textsurface = TTF_RenderText_Solid(textFont, timeText.str().c_str(), textColor);

					if(textsurface == NULL)
					{
						 printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
					}
					else
					{
						SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textsurface);

						if(textTexture == NULL)
						{
							printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
						}
						else
						{
							SDL_Rect textRect = textsurface->clip_rect;
							textRect.x = SCREEN_WIDTH - (textsurface->w + 10);

							SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

							SDL_DestroyTexture(textTexture);
							SDL_FreeSurface(textsurface);
						}
					}

					Character.render();
					finish.render();

					for(unsigned int gateindex = 0; gateindex < gatevector.size(); ++gateindex)
					{
						gatevector[gateindex].render();
					}

					Character.reset = checkGateCollisions(Character.wheelRect, gatevector[0].gateRect, gatevector[0].getFrame()) || 
						checkGateCollisions(Character.wheelRect, gatevector[1].gateRect, gatevector[1].getFrame()) ||
						checkGateCollisions(Character.wheelRect, gatevector[2].gateRect, gatevector[2].getFrame()) ||
						checkGateCollisions(Character.wheelRect, gatevector[3].gateRect, gatevector[3].getFrame()) ||
						checkGateCollisions(Character.wheelRect, gatevector[4].gateRect, gatevector[4].getFrame()) ||
						checkGateCollisions(Character.wheelRect, gatevector[5].gateRect, gatevector[5].getFrame());

					for(unsigned int platformindex = 0; platformindex < platformVector.size(); ++platformindex)
					{
						platformVector[platformindex].render();
					}

					Character.gravity = !checkPlatformCollisions(Character.wheelRect, platformVector[0].platformRect) &&
						!checkPlatformCollisions(Character.wheelRect, platformVector[1].platformRect) &&
						!checkPlatformCollisions(Character.wheelRect, platformVector[2].platformRect);

					for(unsigned int walindex = 0; walindex < wallVector.size(); ++walindex)
					{
						wallVector[walindex].render();
					}

					Character.walkright = checkWalCollisions(Character.wheelRect, wallVector[1].walRect) != 1;
					Character.walkleft = checkWalCollisions(Character.wheelRect, wallVector[0].walRect) != 2;

					if(checkGateCollisions(Character.wheelRect, finish.finishRect, 0))
					{
						SDL_SetRenderDrawColor(renderer,0,0,0,255);
						menu.setEndTime(gameTime);
						menu.setFrame(2);
						menu.active = true;
					}

					//Update screen
					SDL_RenderPresent(renderer);
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}