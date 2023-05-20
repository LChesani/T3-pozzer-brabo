#ifndef __ENEMYWEAPON__H__
#define __ENEMYWEAPON__H__


#include "Weapon.h"
#include "projectile/GuidedProjectile.h"
#include "../canvas/gl_canvas2d.h"


class EnemyWeapon : public Weapon{





public:
    EnemyWeapon(Agent *_user);
    void fire() override;


};


#endif