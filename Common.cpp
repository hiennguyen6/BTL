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
