#include "character.h"

character::character()
{
	wheel = NULL;
	stickcharacter = NULL;
	Renderer = NULL;

	wheelRect.h = HEIGHT;
	wheelRect.w = WIDTH;
	wheelRect.x = 0;
	wheelRect.y = 0;

	walkRects[0].x = 0; walkRects[0].y = 0; walkRects[0].h = 100; walkRects[0].w = 100;
	walkRects[1].x = 100; walkRects[1].y = 0; walkRects[1].h = 100; walkRects[1].w = 100;
	walkRects[2].x = 200; walkRects[2].y = 0; walkRects[2].h = 100; walkRects[2].w = 100;
	walkRects[3].x = 300; walkRects[3].y = 0; walkRects[3].h = 100; walkRects[3].w = 100;
	walkRects[4].x = 400; walkRects[4].y = 0; walkRects[4].h = 100; walkRects[4].w = 100;

	idleRects[0].x = 0; idleRects[0].y = 100; idleRects[0].h = 100; idleRects[0].w = 100;
	idleRects[1].x = 100; idleRects[1].y = 100; idleRects[1].h = 100; idleRects[1].w = 100;
	idleRects[2].x = 200; idleRects[2].y = 100; idleRects[2].h = 100; idleRects[2].w = 100;
	idleRects[3].x = 300; idleRects[3].y = 100; idleRects[3].h = 100; idleRects[3].w = 100;
	idleRects[4].x = 400; idleRects[4].y = 100; idleRects[4].h = 100; idleRects[4].w = 100;

	xvel = 0;
	yvel = 5;
	acceleration = 0;

	resetX = 0;
	resetY = 0;

	walk = false;
	walkright = true;
	walkleft = true;
	gravity = true;
	reset = false;

	degrees = 0;
	frame = 0;
}

void character::load(int Xpos, int Ypos, SDL_Surface* wheelsurface, SDL_Surface* charactersurface, SDL_Renderer* render)
{
	wheelRect.x = Xpos;
	wheelRect.y = Ypos;

	resetX = Xpos;
	resetY = Ypos;
	
	Renderer = render;

	wheel = SDL_CreateTextureFromSurface(Renderer, wheelsurface);
	
	if(wheel == NULL)
	{
		printf("unable to get wheel: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(wheelsurface);
	wheelsurface = NULL;

	stickcharacter = SDL_CreateTextureFromSurface(Renderer, charactersurface);
	
	if(stickcharacter == NULL)
	{
		printf("unable to get character: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(charactersurface);
	charactersurface = NULL;
}

void character::handlekeys(SDL_Event& keyEvent)
{
	//if a key was pressed
	if(keyEvent.type == SDL_KEYDOWN && keyEvent.key.repeat == 0)
	{
		//Adjust the acceleration for the velocity
		if(keyEvent.key.keysym.sym == SDLK_LEFT)
		{
			xvel -= 1;
		}

		if(keyEvent.key.keysym.sym == SDLK_RIGHT)
		{
			xvel += 1;
		}
	}

	//if a key was released
	if(keyEvent.type == SDL_KEYUP && keyEvent.key.repeat == 0)
	{
		//Adjust the acceleration for the velocity
		if(keyEvent.key.keysym.sym == SDLK_LEFT && xvel < 0)
		{
			xvel += 1;
		}

		if(keyEvent.key.keysym.sym == SDLK_RIGHT && xvel > 0)
		{
			xvel -= 1;
		}
	}
}

void character::move()
{	
	if(xvel != 0)
	{
		if((xvel < 0 && walkleft) || (xvel > 0 && walkright))
		{
			wheelRect.x += acceleration * xvel;
			degrees += acceleration * xvel;
		}

		if(acceleration >= 5)
		{
			acceleration = 5;
		}
		else
		{
			acceleration += 1;
		}
		
		walk = true;
	}
	else
	{
		if(acceleration <= 0)
		{
			acceleration = 0;
		}
		else
		{
			acceleration -= 1;
		}
		
		walk = false;
	}

	if(gravity && (wheelRect.y + wheelRect.w) < 800)
	{
		wheelRect.y += yvel;
	}

	if(reset)
	{
		resetPos();
		reset = false;
	}

}

void character::render()
{
	SDL_Rect currentrect;

	if(walk)
	{
		currentrect = walkRects[(int)frame/5];
	}
	else
	{
		currentrect = idleRects[(int)frame/5];
	}
	
	SDL_RenderCopy(Renderer, stickcharacter, &currentrect, &wheelRect);
	SDL_RenderCopyEx(Renderer, wheel, NULL, &wheelRect, degrees, NULL, SDL_FLIP_NONE);

	frame += 0.75;
	
	if(frame / 5 >= ANIMATION_FRAMES)
	{
		frame = 0;
	}
}

void character::free()
{
	SDL_DestroyTexture(wheel);
	wheel = NULL;

	SDL_DestroyTexture(stickcharacter);
	stickcharacter = NULL;
}

void character::resetPos()
{
	wheelRect.x = resetX;
	wheelRect.y = resetY;
	degrees = 0;
}

character::~character()
{
	free();
}