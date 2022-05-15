#include"Bullet.h"

Bullet::Bullet()
{
    x_val=0;
    is_move=false;
}

Bullet::~Bullet()
{

}

void Bullet::HandleBulletMove(const int& x_limit, const int& y_limit)
{
    rect_.x+=x_val;
    if(rect_.x > x_limit)
    {
        is_move=false;
    }
}
