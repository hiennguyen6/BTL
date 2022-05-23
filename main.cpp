#include <iostream>
#include "Common.h"
#include "Character.h"
#include "Threats.h"
#include "Explosion.h"
#include "Power.h"
#include "Text.h"
#include<ctime>
#include<cstdlib>

using namespace std;

LTexture gBackGround;
TTF_Font* gScore=NULL;

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
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
            }
		}
	}

	return success;
}

bool LoadMedia(){
    bool success=true;
    if(!gBackGround.LoadTexture("bkg.jpg", gScreen))
    {
         std::cout << "Failed to load background image" << std::endl;
         success=false;
    }
    gSoundBullet = Mix_LoadWAV("CharBullet.wav");
    if(gSoundBullet==NULL)
    {
        LogError("Failed to load CharBullet sound", MIX_ERROR);
        success=false;
    }
    gSoundExpl = Mix_LoadWAV("Explosion.wav");
    if(gSoundExpl==NULL)
    {
        LogError("Failed to load Expl sound", MIX_ERROR);
        success=false;
    }
    gScore = TTF_OpenFont("Score.ttf", 15);
    if(gScore==NULL)
    {
        LogError("Failed to load font", TTF_ERROR);
        success = false;
    }
    return success;
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
    if(LoadMedia()==false){
        return -1;
    }
    Power pPower;
    Text Score;
    Score.SetColor(Text::WHITE_TEXT);
    Text Time;
    pPower.LoadTexture("Power.png", gScreen);
    pPower.Init();
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
    Explosion Texpl,Texpl2;
    bool tmp=Texpl.LoadEx("exp.png", gScreen);
    bool tmp2=Texpl2.LoadEx("exp.png", gScreen);
    if(!tmp) return -1;
    if(!tmp2) return -1;
    Texpl.SetClip();
    Texpl2.SetClip();

    int powernum=POWER_NUM;
    int scoreval=0;
    bool is_quit=false;
    while(!is_quit){
        while(SDL_PollEvent(&gEvent)!=0){
            if(gEvent.type==SDL_QUIT){
                is_quit=true;
            }
            pPlayer.HandleGetMove(gEvent, gScreen, gSoundBullet);
        }
        SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
        SDL_RenderClear(gScreen);

        bkg_x-=2;
        gBackGround.RenderBackGround(gScreen, bkg_x);
        gBackGround.RenderBackGround(gScreen, bkg_x+SCREEN_WIDTH);
        if(bkg_x <= -SCREEN_WIDTH)
        {
            bkg_x=0;
        }
        pPower.Render(gScreen);

        pPlayer.HandleMove();
        pPlayer.Render(gScreen, NULL);
        pPlayer.HandleBullet(gScreen);

        for(int i=0; i<THREATS_NUM; i++)
        {
            Threats* pThreat = (pThreats + i);



            pThreat->HandleThreatsMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            pThreat->HandleThreatsBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
            pThreat->Render(gScreen, NULL);

            //int framew1=Texpl2.GetFrameWidth();
            //int frameh1=Texpl2.GetFrameHeight();
            int framew=Texpl.GetFrameWidth();
            int frameh=Texpl.GetFrameHeight();
            std::vector<Bullet*> bullet_list = pPlayer.GetBulletList();
            for (int j = 0; j < bullet_list.size(); j++)
            {
                Bullet* pBullet = bullet_list.at(j);
                if(pBullet != NULL)
                {
                    bool is_touch = SDLCommon::CheckTouch(pBullet->GetRect(), pThreat->GetRect());
                    if(is_touch)
                    {
                        scoreval+=5;
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
                        Mix_PlayChannel(-1, gSoundExpl, 0);
                    }
                }
            }
            bool is_touch_2 = SDLCommon::CheckTouch(pThreat->GetRect(), pPlayer.GetRect());
            if(is_touch_2)
            {
                pThreat->ResetThreat(SCREEN_WIDTH + i*SCREEN_WIDTH/4);
            }

            std::vector<Bullet*> Tbullet_list = pThreat->GetBulletList();
            bool is_touch_3=false;
            for (int k = 0; k < Tbullet_list.size(); k++)
            {
                Bullet* pTBullet = Tbullet_list.at(k);
                if(pTBullet != NULL)
                {
                    is_touch_3 = SDLCommon::CheckTouch(pTBullet->GetRect(), pPlayer.GetRect());
                    if(is_touch_3)
                    {
                        pThreat->ResetThreatBullet(pTBullet);
                        break;
                    }
                }
            }
            if(is_touch_2||is_touch_3)
            {
               for(int ex=0; ex<FRAME_NUM; ex++)
                {
                    int xpos=pPlayer.GetRect().x + pPlayer.GetRect().w*0.5 - framew*0.5;
                    int ypos=pPlayer.GetRect().y + pPlayer.GetRect().h*0.5 - frameh*0.5;

                    Texpl.GetFrame(ex);
                    Texpl.SetRect(xpos, ypos);
                    Texpl.Render(gScreen);

                }
                SDL_RenderPresent(gScreen);
                powernum--;
                if(powernum==0)
                {
                   SDL_Delay(500);
                   delete [] pThreats;
                   close();
                   return -1;
                }
                pPower.Decrease();
                pPower.Render(gScreen);

            }


        }
        //Score
        std::string str_scoreval=std::to_string(scoreval);
        std::string str_score("Score:");
        str_score+=str_scoreval;
        Score.SetText(str_score);
        Score.LoadFromRenderText(gScore, gScreen);
        Score.RenderText(gScreen, 500, 10);
        //Time
        std::string str_time("Time:");
        Uint32 timeval=SDL_GetTicks()/1000;
        std::string str_timeval=std::to_string(timeval);
        str_time+=str_timeval;
        Time.SetText(str_time);
        Time.LoadFromRenderText(gScore, gScreen);
        Time.RenderText(gScreen, SCREEN_WIDTH-200, 10);

        SDL_RenderPresent(gScreen);

    }
    close();
    return 0;
}








