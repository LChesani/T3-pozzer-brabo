#ifndef __DEFAULTPROJECTILE__H__
#define __DEFAULTPROJECTILE__H__

#include "Projectile.h"
#include <cmath>




class DefaultProjectile : public Projectile{


public:
    DefaultProjectile(int _x, int _y);
    void render() override;
    void move() override;
    void atualizaHitbox();
    void collider() override;
};






#endif