#include"Character.h"

Character::Character()
{
    rect_.x=0;
    rect_.y=0;
    rect_.w=CHARACTER_WIDTH;
    rect_.h=CHARACTER_HEIGHT;
    x_val=0;
    y_val=0;
}
Character::~Character()
{
    ;
}
void Character::HandleGetMove(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            y_val-=CHARACTER_HEIGHT/5;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            y_val+=CHARACTER_HEIGHT/5;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            x_val+=CHARACTER_WIDTH/5;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            x_val-=CHARACTER_WIDTH/5;
            break;
        default:
            break;
        }

    }
    else if(events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            y_val=0;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            y_val=0;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            x_val=0;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            x_val=0;
            break;
        }
    }
    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
            Bullet* pBullet = new Bullet();
            pBullet->LoadTexture("Bullet.png", screen);
            pBullet->SetRect(this->rect_.x+100, rect_.y+50);
            pBullet->Set_x_val(20);
            pBullet->Set_is_move(true);

            pBulletList.push_back(pBullet);
        }
    }
}
void Character::HandleMove()
{
   rect_.x+=x_val;
   if(rect_.x < 0 || rect_.x + CHARACTER_WIDTH > SCREEN_WIDTH)
   {
       rect_.x-=x_val;
   }
   rect_.y+=y_val;
   if(rect_.y < 0 || rect_.y + CHARACTER_HEIGHT > SCREEN_HEIGHT - 200)
   {
       rect_.y-=y_val;
   }
}
void Character::HandleBullet(SDL_Renderer* des)
{
    for(int i=0; i<pBulletList.size(); i++)
    {
        Bullet* pBullet = pBulletList.at(i);
        if(pBullet != NULL)
        {
            if(pBullet->Get_is_move() == true)
            {
                pBullet->HandleBulletMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                pBullet->Render(des);
            }
            else
            {
                pBulletList.erase(pBulletList.begin() + i);
                if(pBullet != NULL)
                {
                    delete pBullet;
                    pBullet = NULL;
                }
            }
        }
    }
}
void Character::RemoveBullet(const int& index)
{


    if(pBulletList.size()>0 && pBulletList.size()>index)
    {
        Bullet* pBullet = pBulletList.at(index);
        pBulletList.erase(pBulletList.begin() + index);

        if (pBullet != NULL)
        {
            delete pBullet;
            pBullet = NULL;
        }
    }


}
