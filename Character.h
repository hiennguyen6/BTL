#ifndef CHARACTER_H_
#define CHARACTER_H_

#include<vector>
#include"LTexture.h"
#include"Bullet.h"

#define CHARACTER_WIDTH 90
#define CHARACTER_HEIGHT 50

class Character : public LTexture
{
public:
    Character();

    ~Character();

    void HandleGetMove(SDL_Event events, SDL_Renderer* screen);
    void HandleMove();

    void Set_Bullet_List(std::vector<Bullet*> BulletList){pBulletList=BulletList;}
    std::vector<Bullet*> Get_Bullet_list() const {return pBulletList;}
    void HandleBullet(SDL_Renderer* des);

private:
    int x_val;
    int y_val;

    std::vector<Bullet*> pBulletList;
};
#endif
