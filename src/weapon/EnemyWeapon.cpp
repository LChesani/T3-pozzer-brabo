#include "EnemyWeapon.h"



EnemyWeapon::EnemyWeapon(Agent *_user)
{
    setUser(_user);
    cooldown = 100;
    count = 0;
}

void EnemyWeapon::fire()
{
    if(count >= cooldown){
        count = 0;
        GuidedProjectile *p = new GuidedProjectile(getUser()->getX(), getUser()->getY(), getUser()->getTarget());
        projectiles.push_back(p);
    }
}