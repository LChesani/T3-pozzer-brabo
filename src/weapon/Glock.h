#ifndef _GLOCK__H__
#define _GLOCK__H__

#include "Weapon.h"
#include "projectile/RainbowProjectile.h"
#include "../canvas/gl_canvas2d.h"


class Glock : public Weapon{

private:




public:
    Glock(Agent *_user);
    void fire() override;
};


#endif