#include "Common.h"


void LogError(std::string msg, int error_code)
{
	if (error_code == SDL_ERROR)
	{
		std::cout << msg << SDL_GetError() << std::endl;
	}
	if (error_code == IMG_ERROR)
	{
		std::cout << msg << IMG_GetError() << std::endl;
	}
	if (error_code == MIX_ERROR)
	{
		std::cout << msg << Mix_GetError() << std::endl;
	}
	if (error_code == TTF_ERROR)
	{
		std::cout << msg << TTF_GetError() << std::endl;
	}

}
bool SDLCommon::CheckTouch(const SDL_Rect& object1, const SDL_Rect& object2)
{


  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;

}
int SDLCommon::RenderMenu(SDL_Renderer* screen, TTF_Font* font, SDL_Event events, Mix_Chunk* SoundButton)
{
    SDL_Rect MenuItemPos[2];
    MenuItemPos[0].x=550;
    MenuItemPos[0].y=200;

    MenuItemPos[1].x=550;
    MenuItemPos[1].y=250;

    Text Menu[2];
    Menu[0].SetText("Play");
    Menu[0].SetColor(Text::WHITE_TEXT);

    Menu[1].SetText("Exit");
    Menu[1].SetColor(Text::WHITE_TEXT);

    while(true)
    {
        Menu[0].LoadFromRenderText(font, screen);
        Menu[0].RenderText(screen, MenuItemPos[0].x, MenuItemPos[0].y);
        Menu[1].LoadFromRenderText(font, screen);
        Menu[1].RenderText(screen, MenuItemPos[1].x, MenuItemPos[1].y);
        while(SDL_PollEvent(&events)!=0)
        {
            switch(events.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {

                    int xpos=events.motion.x;
                    int ypos=events.motion.y;

                    for(int i=0; i<2; i++)
                    {
                        if(CheckFocus(xpos, ypos, MenuItemPos[i]))
                        {

                            Menu[i].SetColor(Text::BLACK_TEXT);
                        }
                        else
                        {
                            Menu[i].SetColor(Text::WHITE_TEXT);
                        }
                    }
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                {/*
                    SoundButton = Mix_LoadWAV("Button.wav");
                    if(SoundButton==NULL)
                    {
                        LogError("Failed to load Lose sound", MIX_ERROR);
                    }
                    Mix_PlayChannel(-1, SoundButton, 0);*/
                    int xpos=events.motion.x;
                    int ypos=events.motion.y;

                    for(int i=0; i<2; i++)
                    {
                        if(CheckFocus(xpos, ypos, MenuItemPos[i]))
                        {
                            return i;

                        }
                    }
                }
                break;
            case SDL_KEYDOWN:
                if(events.key.keysym.sym==SDLK_ESCAPE)
                {
                    return 1;
                }
                break;

            }
        }
        SDL_RenderPresent(screen);
    }
    return 1;
}
bool SDLCommon::CheckFocus(const int& x, const int& y, const SDL_Rect& rect)
{
    if(x>=rect.x && x<=rect.x+85 &&
       y>=rect.y && y<=rect.y+30)
    {
        return true;
    }
    return false;

}
void DrawEndGameSelection(SDL_Event events, SDL_Renderer* screen, bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(&events) != 0)
			{
				if (events.type == SDL_QUIT)
				{
					Play_Again = false;
					close();
				}

				if (events.type == SDL_KEYDOWN)
				{
					switch (events.key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
				}

			}

		}
	}
}

std::string GetHighScoreFromFile(std::string path)
{
	std::fstream HighScoreFile;
	std::string highscore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(std::string path,
	const int& score,
	const std::string& old_high_score)
{
	int oldHighScore = 0;
	std::fstream HighScoreFile;
	std::string newHighScore;
	std::stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, std::ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	HighScoreFile << newHighScore;
}
/*
void HandlePause(SDL_Event events,
                 SDL_Renderer* screen,
                 LTexture gPause,
                 LTexture gContinue,
                 bool& is_continue)
{
    if(gPause.CheckFocus(events))
    {
        switch(events.type)
        {
        case SDL_MOUSEBUTTONUP:
            is_continue=false;
            SDLCommon::HandleContinue(gContinue, events, screen, is_continue);

        }
    }
}

void HandleContinue(LTexture gContinue,
                    SDL_Event events,
                    SDL_Renderer* screen,
                    bool& is_continue)
{
    bool Back=false;
    while(!Back)
    {
        do
        {
            if(gContinue.CheckFocus(events))
            {
                switch(events.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    Back=true;
                    is_continue=true;
                    break;
                }
            }
            gContinue.RenderBackGround(screen, 10, 10);
            SDL_RenderPresent(screen);
        } while(SDL_WaitEvent(&events)!=0 && events.type==SDL_MOUSEBUTTONDOWN || events.type==SDL_MOUSEMOTION);
    }
}
*/
void close(){
    SDL_DestroyRenderer(gScreen);
	gScreen = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}




