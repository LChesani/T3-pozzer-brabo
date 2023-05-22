#ifndef __RAINBOWPROJECTILE__H__
#define __RAINBOWPROJECTILE__H__

#include "Projectile.h"




class RainbowProjectile : public Projectile{


public:
    bool turn;
    RainbowProjectile(int _x, int _y);
    void render() override;
    void move() override;
    void atualizaHitbox();
    void collider() override;
};






#endif