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
int SDLCommon::RenderMenu(SDL_Renderer* screen, TTF_Font* font, SDL_Event events)
{
    SDL_Rect MenuItemPos[2];
    MenuItemPos[0].x=550;
    MenuItemPos[0].y=200;

    MenuItemPos[1].x=550;
    MenuItemPos[1].y=250;

    Text Menu[2];
    Menu[0].SetText("Play");
    Menu[0].SetColor(Text::BLACK_TEXT);

    Menu[1].SetText("Exit");
    Menu[1].SetColor(Text::BLACK_TEXT);

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
                            Menu[i].SetColor(Text::WHITE_TEXT);
                        }
                        else
                        {
                            Menu[i].SetColor(Text::BLACK_TEXT);
                        }
                    }
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                {
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
    if(x>=rect.x && x<=rect.x+50 &&
       y>=rect.y && y<=rect.y+20)
    {
        return true;
    }
    return false;

}
void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event events,
	SDL_Renderer* screen,
	bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(&events) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					Play_Again = false;
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

			gLoseTexture.Render(screen, 400, 200);

			SDL_RenderPresent(screen);
		}
	}

