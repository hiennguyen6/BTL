#include"Threats.h"

Threats::Threats()
{
    rect_.x=SCREEN_WIDTH;
    rect_.y=0;
    rect_.w=THREATS_WIDTH;
    rect_.h=THREATS_HEIGHT;
    x_val=0;
}
Threats::~Threats()
{

}
void Threats::HandleThreatsMove(const int& x_limit, const int& y_limit)
{
    rect_.x-=x_val;
    if(rect_.x < 0)
    {
        rect_.x=SCREEN_WIDTH;
        int rand_y=rand()%(SCREEN_HEIGHT-200) + 1;
        rect_.y=rand_y;
    }

}
void Threats::GetEvents(SDL_Event events)
{

}
void Threats::GetThreatsBullet(Bullet* pBullet, SDL_Renderer* screen)
{
    pBullet->LoadTexture("Bullet.png", screen);
    pBullet->Set_is_move(true);
    pBullet->SetRect(rect_.x, rect_.y+rect_.h*0.5);
    pBullet->Set_x_val(8);
    pBulletList.push_back(pBullet);

}

void Threats::HandleThreatsBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    for(int i=0; i<pBulletList.size(); i++)
    {
        Bullet* pBullet = pBulletList.at(i);
        if(pBullet != NULL)
        {
            if(pBullet->Get_is_move() == true)
            {
                pBullet->HandleThreatsBulletMove();
                pBullet->Render(des);
            }
            else
            {
                pBullet->Set_is_move(true);
                pBullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);

            }
        }
    }
}
void Threats::ResetThreat(const int& x_limit)
{
    rect_.x=x_limit;
    int rand_y=rand()%(SCREEN_HEIGHT-200) + 1;
    rect_.y=rand_y;

    for(int i=0; i<pBulletList.size(); i++)
    {
        Bullet* pBullet=pBulletList.at(i);
        if(pBullet!=NULL)
        {
            ResetThreatBullet(pBullet);
        }
    }
}
void Threats::ResetThreatBullet(Bullet* pBullet)
{
    pBullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}
