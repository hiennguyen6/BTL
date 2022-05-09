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
