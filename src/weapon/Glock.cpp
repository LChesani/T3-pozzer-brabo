#include "Glock.h"


Glock::Glock(Agent *_user)
{
    setUser(_user);
    baseCooldown = 0.25f;
    setCooldown(1.0f/120.0f);
    count = 999;
}

void Glock::fire()
{
    if(count >= cooldown){
        count = 0;
        RainbowProjectile *p = new RainbowProjectile(getUser()->getX()+getUser()->getWidth()/4, getUser()->getY()+getUser()->getHeight());
        projectiles.push_back(p);
        playAudio("Trab3LuisChesani/src/assets/projectiles/rainbow/sounds/0.wav");
    }
}