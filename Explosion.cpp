#include"Explosion.h"

Explosion::Explosion()
{
    FrameWidth=0;
    FrameHeight=0;
    Frame=0;
}

Explosion::~Explosion()
{

}

bool Explosion::LoadEx(std::string path, SDL_Renderer* screen)
{
    bool tmp = LTexture::LoadTexture(path, screen);
    if(tmp)
    {
        FrameWidth=rect_.w/FRAME_NUM;
        FrameHeight=rect_.h;
    }
    return tmp;
}

void Explosion::SetClip()
{
    FrameClip[0].x = 0;
    FrameClip[0].y = 0;
    FrameClip[0].w = FrameWidth;
    FrameClip[0].h = FrameHeight;

    FrameClip[1].x = FrameWidth;
    FrameClip[1].y = 0;
    FrameClip[1].w = FrameWidth;
    FrameClip[1].h = FrameHeight;

    FrameClip[2].x = 2*FrameWidth;
    FrameClip[2].y = 0;
    FrameClip[2].w = FrameWidth;
    FrameClip[2].h = FrameHeight;

    FrameClip[3].x = 3*FrameWidth;
    FrameClip[3].y = 0;
    FrameClip[3].w = FrameWidth;
    FrameClip[3].h = FrameHeight;
}

void Explosion::Render(SDL_Renderer* screen)
{
    SDL_Rect* current_clip = &FrameClip[Frame];
    SDL_Rect renderspace = {rect_.x, rect_.y, FrameWidth, FrameHeight};
    if(current_clip != NULL)
    {
        renderspace.w = current_clip->w;
        renderspace.h = current_clip->h;
    }
    SDL_RenderCopy(screen, MTexture, current_clip, &renderspace);
}
