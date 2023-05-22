#include "Staff.h"




Staff::Staff(Agent *_user, float _w, float _h){
    sw = _w;
    sh = _h;
    setUser(_user);
    cooldown = 999999; //cast unico, mas poderosa
    count = 999999;
}



void Staff::fire()
{
    if(count >= cooldown){
        count = 0;
        Spell *p = new Spell(getUser()->getX()+getUser()->getWidth()/4, getUser()->getY()+getUser()->getHeight(), sw, sh);
        projectiles.push_back(p);
    }
}