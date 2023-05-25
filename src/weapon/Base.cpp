#include "Base.h"






Base::Base(Agent *_user)
{
    setUser(_user);
    baseCooldown = 0.75f;
    setCooldown(1.0f/120.0f);
    count = 999; //pra comecar atirando ja
}

void Base::fire()
{
    if(count >= cooldown){
        count = 0;
        DefaultProjectile *p = new DefaultProjectile(getUser()->getX()+getUser()->getWidth()/4, getUser()->getY()+getUser()->getHeight());
        projectiles.push_back(p);
        playAudio("Trab3LuisChesani/src/assets/projectiles/default/sounds/0.wav");
    }
}