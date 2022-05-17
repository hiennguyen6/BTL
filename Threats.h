#ifndef THREATS_H_
#define THREATS_H_

#include<vector>
#include"LTexture.h"
#include"Bullet.h"

#define THREATS_WIDTH 80
#define THREATS_HEIGHT 68

class Threats : public LTexture
{
public:
    Threats();
    ~Threats();

    void HandleThreatsMove(const int& x_limit, const int& y_limit);
    void GetEvents(SDL_Event events);

    void Set_x_val(const int& xval){x_val=xval;}
    int Get_x_val() const {return x_val;}

    void Set_Bullet_List(std::vector<Bullet*> BulletList){pBulletList=BulletList;}
    std::vector<Bullet*> Get_Bullet_list() const {return pBulletList;}
    void GetThreatsBullet(Bullet* pBullet, SDL_Renderer* screen);
    void HandleThreatsBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);
private:
    int x_val;
     std::vector<Bullet*> pBulletList;
};

#endif
