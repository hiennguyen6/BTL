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
LTexture gLoseTexture;
TTF_Font* gScore=NULL;
TTF_Font* gMenu=NULL;

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
    if(!gBackGround.LoadTexture("imgs/bkg2.jpg", gScreen))
    {
         std::cout << "Failed to load background image" << std::endl;
         success=false;
    }
    if(!gLoseTexture.LoadTexture("imgs/Lose.png", gScreen))
    {
         std::cout << "Failed to load background image" << std::endl;
         success=false;
    }
    gSoundBullet = Mix_LoadWAV("Sounds/CharBullet.wav");
    if(gSoundBullet==NULL)
    {
        LogError("Failed to load CharBullet sound", MIX_ERROR);
        success=false;
    }
    gSoundExpl = Mix_LoadWAV("Sounds/Explosion.wav");
    if(gSoundExpl==NULL)
    {
        LogError("Failed to load Expl sound", MIX_ERROR);
        success=false;
    }
    gSoundChar = Mix_LoadWAV("Sounds/CharVoice.wav");
    if(gSoundChar==NULL)
    {
        LogError("Failed to load Char sound", MIX_ERROR);
        success=false;
    }
    gSoundLose = Mix_LoadWAV("Sounds/LoseExpl.wav");
    if(gSoundLose==NULL)
    {
        LogError("Failed to load Lose sound", MIX_ERROR);
        success=false;
    }
    gSoundGameOver = Mix_LoadWAV("Sounds/GameOver.wav");
    if(gSoundGameOver==NULL)
    {
        LogError("Failed to load Lose sound", MIX_ERROR);
        success=false;
    }
    gSoundButton = Mix_LoadWAV("Sounds/Button.wav");
    if(gSoundButton==NULL)
    {
        LogError("Failed to load Lose sound", MIX_ERROR);
        success=false;
    }
    gGameMusic = Mix_LoadMUS("Sounds/GameMusic.wav");
	if (gGameMusic == NULL)
	{
		LogError("Failed to load Game music", MIX_ERROR);
		success = false;
	}
	gMenuMusic = Mix_LoadMUS("Sounds/MenuMusic.wav");
	if (gMenuMusic == NULL)
	{
		LogError("Failed to load Game music", MIX_ERROR);
		success = false;
	}
    gScore = TTF_OpenFont("Fonts/Score.ttf", 20);
    if(gScore==NULL)
    {
        LogError("Failed to load font", TTF_ERROR);
        success = false;
    }
    gMenu = TTF_OpenFont("Fonts/Menu.ttf", 40);
    if(gMenu==NULL)
    {
        LogError("Failed to load font", TTF_ERROR);
        success = false;
    }
    return success;
}



int main(int argc, char* argv[])
{
    int Timeval=0;
    double bkg_x=0;
    srand(time(NULL));
    if(Init()==false){
        return -1;
    }
    if(LoadMedia()==false){
        return -1;
    }
    Mix_PlayMusic(gMenuMusic, -1);
    bool Play_Again=true;
    gBackGround.Render(gScreen, NULL);
    SDL_RenderPresent(gScreen);
    int CheckMenu=SDLCommon::RenderMenu(gScreen, gMenu, gEvent, gSoundButton);
    if(CheckMenu==1)
    {
       Play_Again=false;
    }
    while(Play_Again)
    {
        Timeval=0;
        double ThreatsSpeed=3;
        double BkgSpeed=1;
        double TBulletSpeed=8;
        Mix_PlayMusic(gGameMusic, -1);
        Text Score, Time, Lose, HighScore;
        Score.SetColor(Text::WHITE_TEXT);
        Time.SetColor(Text::WHITE_TEXT);
        Lose.SetColor(Text::WHITE_TEXT);
        HighScore.SetColor(Text::WHITE_TEXT);
        Power pPower;
        pPower.LoadTexture("imgs/Power.png", gScreen);
        pPower.Init();
        std::string highscore = GetHighScoreFromFile("highscore.txt");
        // Character
        Character pPlayer;
        pPlayer.SetRect(200,300);
        pPlayer.LoadTexture("imgs/Char.png", gScreen);

        // Threats
        Threats* pThreats = new Threats[THREATS_NUM];
        for(int i=0; i<THREATS_NUM; i++)
        {
           Threats* pThreat = (pThreats + i);
           pThreat->LoadTexture("imgs/Threats.png", gScreen);
           int rand_y=rand()%(SCREEN_HEIGHT-100) + 30;
           pThreat->SetRect(SCREEN_WIDTH + i*SCREEN_WIDTH/4, rand_y);
           pThreat->Set_x_val(ThreatsSpeed);

           Bullet* pBullet = new Bullet();
           pThreat->GetThreatsBullet(pBullet, gScreen);


        }
        Explosion Texpl,Texpl2;
        bool tmp=Texpl.LoadEx("imgs/exp.png", gScreen);
        bool tmp2=Texpl2.LoadEx("imgs/expmain.png", gScreen);
        if(!tmp) return -1;
        if(!tmp2) return -1;
        Texpl.SetClip();
        Texpl2.SetClip();


        int powernum=POWER_NUM;
        int scoreval=0;
        bool is_quit=false;
        while(!is_quit)
        {
            ThreatsSpeed+=0.001;
            BkgSpeed+=0.001;
            TBulletSpeed+=0.001;
            if(ThreatsSpeed==6)
            {
                ThreatsSpeed-=0.001;
            }
            if(BkgSpeed==4)
            {
                BkgSpeed-=0.001;
            }
            while(SDL_PollEvent(&gEvent)!=0){
                if(gEvent.type==SDL_QUIT){
                    is_quit=true;
                    Play_Again=false;
                }
                pPlayer.HandleGetMove(gEvent, gScreen, gSoundBullet);
            }
            SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
            SDL_RenderClear(gScreen);

            bkg_x-=BkgSpeed;
            gBackGround.RenderBackGround(gScreen, bkg_x, 0);
            gBackGround.RenderBackGround(gScreen, bkg_x+SCREEN_WIDTH, 0);
            if(bkg_x <= -SCREEN_WIDTH)
            {
                bkg_x=0;
            }

            //Time
            Timeval+=1;

            pPower.Render(gScreen);

            pPlayer.HandleMove();
            pPlayer.Render(gScreen, NULL);
            pPlayer.HandleBullet(gScreen);

            for(int i=0; i<THREATS_NUM; i++)
            {
                Threats* pThreat = (pThreats + i);


                pThreat->Set_x_val(3);
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
                            scoreval+=100;
                            for(int ex=0; ex<FRAME_NUM; ex++)
                            {
                                int xpos=pBullet->GetRect().x - framew*0.5;
                                int ypos=pBullet->GetRect().y - frameh*0.5;

                                Texpl.GetFrame(ex);
                                Texpl.SetRect(xpos, ypos);
                                Texpl.Render(gScreen);

                            }
                            pThreat->ResetThreat(SCREEN_WIDTH + i*SCREEN_WIDTH/4);

                            if(pThreat->GetBulletList().size()==0)
                            {
                                Bullet* pBullet = new Bullet();
                                pThreat->GetThreatsBullet(pBullet, gScreen);
                            }

                            pThreat->RemoveBullet();

                            pPlayer.RemoveBullet(j);
                            Mix_PlayChannel(-1, gSoundExpl, 0);
                        }
                     }
                }
                //Score
                std::string str=std::to_string(Timeval);
                int tmp=stoi(str);
                tmp+=scoreval;
                std::string str_scoreval=std::to_string(tmp);
                std::string str_score("Score:");
                str_score+=str_scoreval;
                Score.SetText(str_score);
                Score.LoadFromRenderText(gScore, gScreen);
                Score.RenderText(gScreen, SCREEN_WIDTH-200, 10);
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
                int framew2=Texpl2.GetFrameWidth();
                int frameh2=Texpl2.GetFrameHeight();
                if(is_touch_2||is_touch_3)
                {

                    for(int ex=0; ex<FRAME_NUM; ex++)
                    {
                        int xpos=pPlayer.GetRect().x + pPlayer.GetRect().w*0.5 - framew2*0.5;
                        int ypos=pPlayer.GetRect().y + pPlayer.GetRect().h*0.5 - frameh2*0.5;

                        Texpl2.GetFrame(ex);
                        Texpl2.SetRect(xpos, ypos);
                        Texpl2.Render(gScreen);

                    }
                    SDL_RenderPresent(gScreen);
                    powernum--;
                    if(powernum==0)
                    {
                       Mix_PauseMusic();
                       Mix_PlayChannel(-1, gSoundLose, 0);
                       UpdateHighScore("highscore.txt", tmp, highscore);
                       SDL_Delay(1000);
                       delete [] pThreats;
                       Mix_PlayChannel(-1, gSoundGameOver, 0);
                       is_quit=true;
                       break;
                       //close();
                       //return -1;
                    }
                    pPower.Decrease();
                    pPower.Render(gScreen);
                    Mix_PlayChannel(-1, gSoundChar, 0);
                }


            }
            //Time
            std::string str_time("Time:");
            std::string str_timeval=std::to_string(Timeval);
            str_time+=str_timeval;
            Time.SetText(str_time);
            Time.LoadFromRenderText(gScore, gScreen);
            Time.RenderText(gScreen, 500, 10);

            //highscore
            std::string str_highscore("High score:");
            str_highscore+=highscore;
            HighScore.SetText(str_highscore);
            HighScore.LoadFromRenderText(gScore, gScreen);
            HighScore.RenderText(gScreen, SCREEN_WIDTH-200, 40);


            SDL_RenderPresent(gScreen);

        }
        gLoseTexture.RenderBackGround(gScreen, 275, 200);
        Lose.SetText("Press SPACE to play again or press ESC to exit");
        Lose.LoadFromRenderText(gMenu, gScreen);
        Lose.RenderText(gScreen, 100, 80);
        SDL_RenderPresent(gScreen);
        DrawEndGameSelection(gEvent, gScreen, Play_Again);

    }

    close();
    return 0;
}








