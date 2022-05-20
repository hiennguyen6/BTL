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

}
bool SDLCommon::CheckTouch(const SDL_Rect& object1, const SDL_Rect& object2)
{


  // Case 1: size object 1 < size object 2
  if (object1.x > object2.x && object1.x < object2.x + object2.w)
  {
    if (object1.y > object2.y && object1.y < object2.y + object2.h)
    {
      return true;
    }
  }

  if (object1.x > object2.x && object1.x < object2.x + object2.w)
  {
    if (object1.y + object1.h > object2.y && object1.y + object1.h < object2.y + object2.h)
    {
      return true;
    }
  }

  if (object1.x + object1.w > object2.x && object1.x + object1.w < object2.x + object2.w)
  {
    if (object1.y > object2.y && object1.y < object2.y + object2.h)
    {
      return true;
    }
  }

  if (object1.x + object1.w > object2.x && object1.x + object1.w < object2.x + object2.w)
  {
    if (object1.y + object1.h > object2.y && object1.y + object1.h < object2.y + object2.h)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (object2.x > object1.x && object2.x < object1.x + object1.w)
  {
    if (object2.y > object1.y && object2.y < object1.y + object1.h)
    {
      return true;
    }
  }

  if (object2.x > object1.x && object2.x < object1.x + object1.w)
  {
    if (object2.y + object2.h > object1.y && object2.y + object2.h < object1.y + object1.h)
    {
      return true;
    }
  }

  if (object2.x + object2.w > object1.x && object2.x + object2.w < object1.x + object1.w)
  {
    if (object2.y > object1.y && object2.y < object1.y + object1.h)
    {
      return true;
    }
  }

  if (object2.x + object2.w > object1.x && object2.x + object2.w < object1.x + object1.w)
  {
    if (object2.y + object2.h > object1.y && object2.y + object2.h < object1.y + object1.h)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (object1.y == object2.y && object1.x + object1.w == object2.x + object2.w && object1.y + object1.h == object2.y + object2.h)
  {
    return true;
  }

  return false;
}

