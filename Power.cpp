#include "Power.h"

Power::Power()
{

}

Power::~Power()
{

}

void Power::SetPos(const int& pos)
{
  PosList.push_back(pos);
}


void Power::Render(SDL_Renderer* screen)
{
  if (number == PosList.size())
  {
    for (int i = 0; i < PosList.size(); i++)
    {
      rect_.x = PosList.at(i);
      SDL_Rect RenderSpace = {rect_.x, rect_.y, rect_.w, rect_.h };

	  SDL_RenderCopy(screen, MTexture, NULL, &RenderSpace);
    }
  }
}

void Power::Init()
{
  number = 3;
  if (PosList.size() > 0)
  {
    PosList.clear();
  }

  SetPos(20);
  SetPos(50);
  SetPos(80);
}

void Power::Decrease()
{
  number--;
  PosList.pop_back();
}

