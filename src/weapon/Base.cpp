#include "Base.h"
#include "../canvas/gl_canvas2d.h"






Base::Base(Agent *_user)
{
    setUser(_user);
    cooldown = 25;
    count = 0;
}

void Base::fire()
{
    if(count >= cooldown){
        count = 0;
        DefaultProjectile *p = new DefaultProjectile(getUser()->getX(), getUser()->getY());
        projectiles.push_back(p);
    }
}