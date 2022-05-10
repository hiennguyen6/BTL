#ifndef CHARACTER_
#define CHARACTER_

#include"LTexture.h"

#define CHARACTER_WIDTH 90
#define CHARACTER_HEIGHT 50

class Character : public LTexture
{
public:
    Character();

    ~Character();

private:
    int x_val;
    int y_val;
};
#endif
