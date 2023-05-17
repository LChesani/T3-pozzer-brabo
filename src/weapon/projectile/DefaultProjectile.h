#ifndef __DEFAULTPROJECTILE__H__
#define __DEFAULTPROJECTILE__H__

#include "Projectile.h"





class DefaultProjectile : public Projectile{


public:
    DefaultProjectile(int _x, int _y);
    void render() override;
    void move() override;
};






#endif