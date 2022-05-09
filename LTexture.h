#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "Common.h"

class LTexture
{
public:
	LTexture();

	~LTexture();

	void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}

	SDL_Rect GetRect() const {return rect_;}
	SDL_Texture* GetTexture() const {return MTexture;}

	void Free();

	bool LoadTexture(std::string path, SDL_Renderer *gRenderer);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

protected:
	SDL_Texture* MTexture;
	SDL_Rect rect_;
};

#endif