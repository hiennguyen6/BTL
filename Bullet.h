#ifndef BULLET_H_
#define BULLET_H_

#include"LTexture.h"

class Bullet : public LTexture
{
public:
    Bullet();
    ~Bullet();

    void Set_x_val(const int& xval){x_val=xval;}
    int Get_x_val() const {return x_val;}

    void Set_is_move(const bool& ismove){is_move=ismove;}
    bool Get_is_move() const {return is_move;}

    void HandleBulletMove(const int& x_limit, const int& y_limit);
private:
    int x_val;
    bool is_move;
};
#endif
