#ifndef _STAFF__H__
#define _STAFF__H__

#include "Weapon.h"
#include "projectile/Spell.h"
#include "../canvas/gl_canvas2d.h"


class Staff : public Weapon{

protected:
    float sw, sh;
    bool fired;


public:
    Staff(Agent *_user, float _w, float _h);
    void fire() override;
};


#endif