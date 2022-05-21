#include <iostream>
#include "Common.h"
#include "Character.h"
#include "Threats.h"
#include "Explosion.h"
#include<ctime>
#include<cstdlib>

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
    int bkg_x=0;
    srand(time(NULL));
    if(Init()==false){
        return -1;
    }
    if(LoadBackGround()==false){
        return -1;
    }
    // Character
    Character pPlayer;
    pPlayer.SetRect(200,300);
    pPlayer.LoadTexture("Char.png", gScreen);

    // Threats
    Threats* pThreats = new Threats[THREATS_NUM];
    for(int i=0; i<THREATS_NUM; i++)
    {
       Threats* pThreat = (pThreats + i);
       pThreat->LoadTexture("Threats.png", gScreen);
       int rand_y=rand()%(SCREEN_HEIGHT-200) + 1;
       pThreat->SetRect(SCREEN_WIDTH + i*SCREEN_WIDTH/4, rand_y);
       pThreat->Set_x_val(3);

       Bullet* pBullet = new Bullet();
       pThreat->GetThreatsBullet(pBullet, gScreen);

    }
    Explosion Texpl;
    bool tmp=Texpl.LoadEx("exp.png", gScreen);
    if(!tmp) return -1;
    Texpl.SetClip();


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

        bkg_x-=1;
        gBackGround.RenderBackGround(gScreen, bkg_x);
        gBackGround.RenderBackGround(gScreen, bkg_x+SCREEN_WIDTH);
        if(bkg_x <= -SCREEN_WIDTH)
        {
            bkg_x=0;
        }
        pPlayer.Render(gScreen, NULL);
        pPlayer.HandleMove();
        pPlayer.HandleBullet(gScreen);

        for(int i=0; i<THREATS_NUM; i++)
        {
            Threats* pThreat = (pThreats + i);


            pThreat->Render(gScreen, NULL);
            pThreat->HandleThreatsMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            pThreat->HandleThreatsBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);

            bool is_touch = SDLCommon::CheckTouch(pPlayer.GetRect(), pThreat->GetRect());
            if(is_touch)
            {
                delete [] pThreats;
                close();
                return -1;
            }
            int framew=Texpl.GetFrameWidth();
            int frameh=Texpl.GetFrameHeight();
            std::vector<Bullet*> bullet_list = pPlayer.GetBulletList();
            for (int j = 0; j < bullet_list.size(); j++)
            {
                Bullet* pBullet = bullet_list.at(j);
                if(pBullet != NULL)
                {
                    bool is_touch_2 = SDLCommon::CheckTouch(pBullet->GetRect(), pThreat->GetRect());
                    if(is_touch_2)
                    {
                        for(int ex=0; ex<FRAME_NUM; ex++)
                        {
                            int xpos=pBullet->GetRect().x - framew*0.5;
                            int ypos=pBullet->GetRect().y - frameh*0.5;

                            Texpl.GetFrame(ex);
                            Texpl.SetRect(xpos, ypos);
                            Texpl.Render(gScreen);

                        }
                        pThreat->ResetThreat(SCREEN_WIDTH + i*SCREEN_WIDTH/4);
                        pPlayer.RemoveBullet(j);
                    }
                }
            }

            std::vector<Bullet*> Tbullet_list = pThreat->GetBulletList();
            for (int k = 0; k < Tbullet_list.size(); k++)
            {
                Bullet* pTBullet = Tbullet_list.at(k);
                if(pTBullet != NULL)
                {
                    bool is_touch_3 = SDLCommon::CheckTouch(pTBullet->GetRect(), pPlayer.GetRect());
                    if(is_touch_3)
                    {
                        pThreat->RemoveBullet(k);
                        delete [] pThreats;
                        close();
                        return -1;
                    }
                }
            }




        }
        SDL_RenderPresent(gScreen);

    }
    close();
    return 0;
}








