#include "Glock.h"


Glock::Glock(Agent *_user)
{
    setUser(_user);
    cooldown = 20;
    count = 0;
}

void Glock::fire()
{
    if(count >= cooldown){
        count = 0;
        RainbowProjectile *p = new RainbowProjectile(getUser()->getX()+getUser()->getWidth()/4, getUser()->getY()+getUser()->getHeight());
        projectiles.push_back(p);
        playAudio("Trab3 (malvado)/src/assets/projectiles/rainbow/sounds/0.wav");
    }
}