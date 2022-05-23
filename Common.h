#ifndef COMMON_
#define COMMON_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

const std::string WINDOW_TITLE = "AirPlane";


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;

static Mix_Chunk* gSoundBullet;
static Mix_Chunk* gSoundExpl;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int THREATS_NUM = 5;
const int POWER_NUM = 3;

void LogError(std::string msg, int error_code);

namespace SDLCommon
{
    bool CheckTouch(const SDL_Rect& object1, const SDL_Rect& object2 );
}

#endif
