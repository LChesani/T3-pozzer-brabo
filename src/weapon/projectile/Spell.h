#ifndef __SPELL__H__
#define __SPELL__H__

#include "Projectile.h"

class Spell : public Projectile{

protected:
    float sw, sh;
    bool boom = false;
    float r;
    float g;
    float b;
public:
    int frameColor;
    float dim;
    Spell(int _x, int _y, float _w, float _h);
    bool turn;
    void render() override;
    void move() override;
    void explosion();
    void collider() override;
    void atualizaHitbox();
    void setAlive() override;
};






#endif