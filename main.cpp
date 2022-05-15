#include <iostream>
#include "Common.h"
#include "Character.h"

using namespace std;

LTexture gBackGround;

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gScreen == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
			    SDL_SetRenderDrawColor(gScreen, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}
            }
		}
	}

	return success;
}

bool LoadBackGround(){
    bool tmp=gBackGround.LoadTexture("bkg.jpg", gScreen);
    return tmp;
}

void close(){
    SDL_DestroyRenderer(gScreen);
	gScreen = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(Init()==false){
        return -1;
    }
    if(LoadBackGround()==false){
        return -1;
    }
    Character pPlayer;
    pPlayer.SetRect(200,300);
    pPlayer.LoadTexture("Char.png", gScreen);
    bool is_quit=false;
    while(!is_quit){
        while(SDL_PollEvent(&gEvent)!=0){
            if(gEvent.type==SDL_QUIT){
                is_quit=true;
            }
            pPlayer.HandleGetMove(gEvent, gScreen);
        }
        SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
        SDL_RenderClear(gScreen);

        gBackGround.Render(gScreen, NULL);
        pPlayer.Render(gScreen, NULL);
        pPlayer.HandleMove();
        pPlayer.HandleBullet(gScreen);



        SDL_RenderPresent(gScreen);
    }
    return 0;
}








