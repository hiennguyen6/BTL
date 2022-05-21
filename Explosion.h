#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "LTexture.h"

#define FRAME_NUM 4

class Explosion : public LTexture
{

public:
    Explosion();
    ~Explosion();

    void SetClip();
    void GetFrame(const int& f) {Frame=f;}
    bool LoadEx(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);
    int GetFrameWidth() const {return FrameWidth;}
    int GetFrameHeight() const {return FrameHeight;}

private:
    int FrameWidth;
    int FrameHeight;
    int Frame;
    SDL_Rect FrameClip[FRAME_NUM];
};
#endif // EXPLOSION_H_
