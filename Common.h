#ifndef COMMON_
#define COMMON_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Text.h"
#include "LTexture.h"


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
static Mix_Chunk* gSoundChar;
static Mix_Chunk* gSoundLose;
static Mix_Chunk* gSoundGameOver;
static Mix_Chunk* gSoundButton;
static Mix_Music* gGameMusic;
static Mix_Music* gMenuMusic;


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int THREATS_NUM = 4;
const int POWER_NUM = 3;

void LogError(std::string msg, int error_code);

void DrawEndGameSelection(SDL_Event events, SDL_Renderer* screen, bool &Play_Again);

std::string GetHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path, const int& score, const std::string& old_high_score);

/*void HandleContinue(SDL_Event events, SDL_Renderer* screen,LTexture gContinue, bool& is_continue);

void HandlePause(SDL_Event events, SDL_Renderer* screen, LTexture gPause, LTexture gContinue, bool& is_continue);*/


void close();


namespace SDLCommon
{

    bool CheckTouch(const SDL_Rect& object1, const SDL_Rect& object2 );
    int RenderMenu(SDL_Renderer* screen, TTF_Font* font, SDL_Event events, Mix_Chunk* SoundButton);
    bool CheckFocus(const int& x, const int& y, const SDL_Rect& rect);

}

#endif
