#ifndef TEXT_H_
#define TEXT_H_

#include"Common.h"

class Text
{
public:
    Text();
    ~Text();

    enum TextColor
    {
       RED_TEXT  = 0,
       WHITE_TEXT = 1,
       BLACK_TEXT = 2,
    };
    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);
    void RenderText(SDL_Renderer*screen,
                    int x, int y,
                    SDL_Rect* clip=NULL,
                    double angle=0.0,
                    SDL_Point* center=NULL,
                    SDL_RendererFlip flip=SDL_FLIP_NONE);
    int GetWidth() const {return Width;}
    int GetHeight() const {return Height;}
    void SetText(const std::string& text) {strval=text;}
    std::string GetText() const {return strval;}

private:
    std::string strval;
    SDL_Color TextColor;
    SDL_Texture* Texture;
    int Width;
    int Height;

};
#endif // TEXT_H_
