#include"Text.h"

Text::Text()
{
    TextColor.r=255;
    TextColor.g=255;
    TextColor.b=255;
    Texture=NULL;
}
Text::~Text()
{

}
void Text::Free()
{
    if(Texture!=NULL)
    {
        SDL_DestroyTexture(Texture);
        Texture=NULL;
    }
}
bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer*screen)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, strval.c_str(), TextColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		Texture = SDL_CreateTextureFromSurface(screen, textSurface);
		if (Texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			Width = textSurface->w;
			Height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return Texture != NULL;
}

void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    TextColor.r=red;
    TextColor.g=green;
    TextColor.b=blue;
}

void Text::SetColor(int type)
{
    SDL_Color color;
    switch(type)
    {
    case RED_TEXT:
        color={255, 0, 0};
        break;
    case WHITE_TEXT:
        color={255, 255, 255};
        break;
    case BLACK_TEXT:
        color={0, 0, 0};
        break;
    }
    TextColor=color;
}
void Text::RenderText(SDL_Renderer*screen,
                    int x, int y,
                    SDL_Rect* clip,
                    double angle,
                    SDL_Point* center,
                    SDL_RendererFlip flip)
{
    SDL_Rect renderspace = {x, y, Width, Height};
    if(clip!=NULL)
    {
        renderspace.w=clip->w;
        renderspace.h=clip->h;
    }
    SDL_RenderCopyEx(screen, Texture, clip, &renderspace, angle, center, flip);
}


