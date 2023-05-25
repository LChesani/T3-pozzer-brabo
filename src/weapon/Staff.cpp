#include "Staff.h"




Staff::Staff(Agent *_user, float _w, float _h){
    sw = _w;
    sh = _h;
    baseCooldown = 999998; //cast unico, mas poderosa
    setCooldown(1);
    setUser(_user);
    fired = false;
    count = 999999;
}



void Staff::fire()
{
    if(!fired){
        fired = true;
        Spell *p = new Spell(getUser()->getX()+getUser()->getWidth()/4, getUser()->getY()+getUser()->getHeight(), sw, sh);
        projectiles.push_back(p);
    }
}