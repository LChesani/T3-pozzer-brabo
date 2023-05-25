#include "EnemyWeapon.h"



EnemyWeapon::EnemyWeapon(Agent *_user)
{
    setUser(_user);
    baseCooldown = 3.0f;
    setCooldown(1.0f/120.0f);
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