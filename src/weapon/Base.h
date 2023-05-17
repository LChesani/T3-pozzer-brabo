#ifndef _BASE__H__
#define _BASE__H__

#include "Weapon.h"
#include "projectile/DefaultProjectile.h"



class Base : public Weapon{

private:




public:
    Base(Agent *_user);
    void fire() override;


};






















#endif