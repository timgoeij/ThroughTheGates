#include "Mainmenu.h"

Mainmenu::Mainmenu(void)
{
	active = true;
	quit = false;

	MouseX = 0;
	MouseY = 0;

	frame = 0;

	EndTime = 0;

	textFont = NULL;

	//set the text color to white
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	textColor.a = 255;

	Renderer = NULL;
	menuTexture = NULL;
	helpTexture = NULL;
	timeTexture = NULL;

	//initialize source rects
	for(int index = 0; index < BUTTON_FRAMES; ++index)
	{
		if(index == 0)
		{
			startButtons[index].x = 0;
			helpButtons[index].x = 0;
			quitBackButtons[index].x = 0;
		}
		else
		{
			startButtons[index].x = 400;
			helpButtons[index].x = 400;
			quitBackButtons[index].x = 400;
		}

		startButtons[index].y = 100; startButtons[index].h = 100; startButtons[index].w = 400;
		helpButtons[index].y = 200; helpButtons[index].h = 100; helpButtons[index].w = 400;
		quitBackButtons[index].y = 300; quitBackButtons[index].h = 100; quitBackButtons[index].w = 400;
	}

	titleRect.x = 0; titleRect.y = 0; titleRect.h = 100; titleRect.w = 400;
	endTitleRect.x = 400; endTitleRect.y = 0; endTitleRect.h = 100; endTitleRect.w = 400;
	helpRect.x = 0; helpRect.y = 0; helpRect.h = 300; helpRect.w = 800;

	//initialize destination rects
	title.x = (1000 / 2) - (400 / 2); title.y = 50; title.h = 100; title.w = 400;
	help.x = (1000 / 2) - (800 / 2); help.y = 100; help.h = 300; help.w = 800;

	for(int index = 0; index < MENU_BUTTONS; ++index)
	{
		if(index == 0)
		{
			buttons[index].y = 250;
		}
		else if(index == 1)
		{
			buttons[index].y = 450;
		}
		else
		{
			buttons[index].y = 650;
		}

		buttons[index].x = (1000 / 2) - (400 / 2); buttons[index].h = 100; buttons[index].w = 400;

		//initialize selection bools for menu buttons
		selected[index] = false;
	}

	//initialize selection bool for help- and endscreen button
	select = false;
}

void Mainmenu::load(SDL_Surface* menuSurface,  SDL_Surface* helpSurface, TTF_Font* font, SDL_Renderer* render)
{
	Renderer = render;

	textFont = font;

	menuTexture = SDL_CreateTextureFromSurface(Renderer, menuSurface);
	helpTexture = SDL_CreateTextureFromSurface(Renderer, helpSurface);


	if(menuTexture == NULL)
	{
		printf("unable to get menu: sdl error %s", SDL_GetError());
	}

	if(helpTexture == NULL)
	{
		printf("unable to get helpmenu: sdl error %s", SDL_GetError());
	}

	SDL_FreeSurface(menuSurface);
	SDL_FreeSurface(helpSurface);
}

void Mainmenu::handlemouse(SDL_Event& mouseEvent)
{
	//get the position from the mouse
	SDL_GetMouseState(&MouseX, &MouseY);

	if(frame == 0)
	{
		for(int buttonIndex = 0; buttonIndex < MENU_BUTTONS; ++buttonIndex)
		{
			if((MouseX >= buttons[buttonIndex].x && MouseX <= (buttons[buttonIndex].x + buttons[buttonIndex].w)) &&
				(MouseY >= buttons[buttonIndex].y && MouseY <= (buttons[buttonIndex].y + buttons[buttonIndex].h)))
			{
				selected[buttonIndex] = true;

				if(mouseEvent.type == SDL_MOUSEBUTTONUP && mouseEvent.button.button == 1)
				{
					switch(buttonIndex)
					{
					case 0: SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
						active = false;
						break;
					case 1: frame = 1;
						selected[buttonIndex] = false;
						break;
					case 2: quit = true;
						break;
					}
				}
			}
			else
			{
				selected[buttonIndex] = false;
			}
		}
	}
	else
	{
		if((MouseX >= buttons[2].x && MouseX <= (buttons[2].x + buttons[2].w)) &&
			(MouseY >= buttons[2].y && (MouseY <= buttons[2].y + buttons[2].h)))
		{
			select = true;

			if(mouseEvent.type == SDL_MOUSEBUTTONUP && mouseEvent.button.button == 1)
			{
				if(frame == 1)
				{
					frame = 0;
					select = false;
				}
				else
				{
					quit = true;
				}
			}
		}
		else
		{
			select = false;
		}
	}
}

void Mainmenu::render()
{
#pragma region menu screen
	if(frame == 0)
	{
	
		SDL_Rect currentStartButton;
		SDL_Rect currentQuitButton;
		SDL_Rect currentHelpButton;

		for(int selectIndex = 0; selectIndex < MENU_BUTTONS; ++selectIndex)
		{
			if(!selected[selectIndex])
			{
				switch(selectIndex)
				{
				case 0: currentStartButton = startButtons[0];
				break;
				case 1: currentHelpButton = helpButtons[0];
				break;
				case 2: currentQuitButton = quitBackButtons[0];
				break;
				}
			}
			else
			{
				switch(selectIndex)
				{
				case 0: currentStartButton = startButtons[1];
				break;
				case 1: currentHelpButton = helpButtons[1];
				break;
				case 2: currentQuitButton = quitBackButtons[1];
				break;
				}
			}

			switch(selectIndex)
			{
				case 0: SDL_RenderCopy(Renderer, menuTexture, &currentStartButton, &buttons[selectIndex]);
				break;
				case 1: SDL_RenderCopy(Renderer, menuTexture, &currentHelpButton, &buttons[selectIndex]);
				break;
				case 2: SDL_RenderCopy(Renderer, menuTexture, &currentQuitButton, &buttons[selectIndex]);
				break;
			}
		}

		SDL_RenderCopy(Renderer, menuTexture, &titleRect, &title);
	}
#pragma endregion
#pragma region help and end screen
	else
	{
		SDL_Rect currentButton;

		if(!select)
		{
			currentButton = quitBackButtons[0];
		}
		else
		{
			currentButton = quitBackButtons[1];
		}

		if(frame == 1)
		{
			SDL_RenderCopy(Renderer, helpTexture, &helpRect, &help);
			SDL_RenderCopy(Renderer, helpTexture, &currentButton, &buttons[2]);
		}
		else
		{	
			SDL_RenderCopy(Renderer, menuTexture, &endTitleRect, &title);
			SDL_RenderCopy(Renderer, timeTexture, NULL, &timeRect);
			SDL_RenderCopy(Renderer, menuTexture, &currentButton, &buttons[2]);
		}
	}
}
#pragma endregion
void Mainmenu::setFrame(int Frame)
{
	frame = Frame;
}

void Mainmenu::setEndTime(Uint32 endTime)
{
	EndTime = endTime;

	std::stringstream timeText;
	timeText<<"In "<<EndTime<<" Seconds";

	SDL_Surface* timeSurface = TTF_RenderText_Blended(textFont,timeText.str().c_str(),textColor);

	if(timeSurface == NULL)
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		timeTexture = SDL_CreateTextureFromSurface(Renderer, timeSurface);

		if(timeTexture == NULL)
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			timeRect = timeSurface->clip_rect;
			timeRect.x = (1000 / 2) - (timeSurface->w / 2);
			timeRect.y = 300;

			SDL_FreeSurface(timeSurface);
		}
	}
}

void Mainmenu::free()
{
	SDL_DestroyTexture(menuTexture);
	SDL_DestroyTexture(helpTexture);
	SDL_DestroyTexture(timeTexture);
	menuTexture = NULL;
	helpTexture = NULL;
	timeTexture = NULL;

	TTF_CloseFont(textFont);
	textFont = NULL;
}

Mainmenu::~Mainmenu(void)
{
	free();
}
