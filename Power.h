#ifndef POWER_H_
#define POWER_H_

#include"LTexture.h"
#include<vector>

class Power : public LTexture
{
public:
    Power();
    ~Power();
    void SetNumber(const int& num) {number = num;}
    void SetPos (const int& pos);
    void Render(SDL_Renderer* des);
    void Init();
    void Decrease();
private:
    int number;
    std::vector <int> PosList;
};


#endif
