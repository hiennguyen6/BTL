#ifndef BULLET_H_
#define BULLET_H_

#include"LTexture.h"

#define CHAR_B_WIDTH
#define CHAR_B_HEIGHT

#define THR_B_WIDTH
#define THR_B_HEIGHT

class Bullet : public LTexture
{
public:
    Bullet();
    ~Bullet();

    void Set_x_val(const int& xval){x_val=xval;}
    int Get_x_val() const {return x_val;}

    void Set_Type(const int& type){Bullet_type=type;}
    int Get_Type() const {return Bullet_type;}
    void SetBulletSize(const int& w, const int& h){rect_.w=w, rect_.h=h;}

    void Set_is_move(const bool& ismove){is_move=ismove;}
    bool Get_is_move() const {return is_move;}

    void HandleBulletMove(const int& x_limit, const int& y_limit);
    void HandleThreatsBulletMove();
private:
    int x_val;
    bool is_move;
    int Bullet_type;
};
#endif
