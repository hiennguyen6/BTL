#include "LTexture.h"

LTexture::LTexture()
{
	MTexture = nullptr;
    rect_.x=0;
    rect_.y=0;
    rect_.w=0;
    rect_.h=0;
}

LTexture::~LTexture()
{
	Free();
}

void LTexture::Free()
{
	if (MTexture != nullptr)
	{
	    SDL_DestroyTexture(MTexture);
		MTexture = nullptr;
		rect_.w = 0;
		rect_.h = 0;
	}
}

bool LTexture::LoadTexture(std::string path, SDL_Renderer *screen)
{
	Free();

	SDL_Texture* NewTexture = nullptr;

	SDL_Surface* LoadedSurface = IMG_Load(path.c_str());
	if (LoadedSurface == nullptr)
	{
		LogError("Can not load image.", IMG_ERROR);
	}
	else
	{
	    SDL_SetColorKey(LoadedSurface, SDL_TRUE, SDL_MapRGB(LoadedSurface->format, 0, 255, 255));
		NewTexture = SDL_CreateTextureFromSurface(screen, LoadedSurface);
		if (NewTexture == nullptr)
		{
			LogError("Can not create texture from surface.", SDL_ERROR);
		}
		else
		{
			rect_.w = LoadedSurface->w;
			rect_.h = LoadedSurface->h;
		}

		SDL_FreeSurface(LoadedSurface);
	}

	MTexture = NewTexture;

	return MTexture != nullptr;
}

void LTexture::Render(SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	SDL_Rect RenderSpace = {rect_.x, rect_.y, rect_.w, rect_.h };

	SDL_RenderCopy(gRenderer, MTexture, clip, &RenderSpace);
}
void LTexture::RenderBackGround(SDL_Renderer* screen, double xoffset, double yoffset)
{
    rect_.x=xoffset;
    rect_.y=yoffset;
    SDL_Rect RenderSpace = {rect_.x, rect_.y, rect_.w, rect_.h };

	SDL_RenderCopy(screen, MTexture, NULL, &RenderSpace);
}

bool LTexture::CheckFocus(SDL_Event events)
{
     if (events.type == SDL_MOUSEMOTION || events.type == SDL_MOUSEBUTTONDOWN || events.type == SDL_MOUSEBUTTONUP)
	{
        int x,y;
        SDL_GetMouseState(&x, &y);
		bool check = true;
		if (x < rect_.x)
		{
			check = false;
		}
		else if (x > rect_.x + 40)
		{
			check = false;
		}
		else if (y < rect_.y)
		{
			check = false;
		}
		else if (y > rect_.y + 40)
		{
			check = false;
		}
		return check;
	}
	return false;
}

