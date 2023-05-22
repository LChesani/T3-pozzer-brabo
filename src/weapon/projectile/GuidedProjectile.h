#ifndef __GUIDEDPROJECTILE__H__
#define __GUIDEDPROJECTILE__H__

#include "Projectile.h"
#include "../../agent/Agent.h"
#include <cmath>


class GuidedProjectile : public Projectile{

protected:
    Agent *target;
    Vector2 direction;
public:
    GuidedProjectile(int _x, int _y, Agent *_target);
    void render() override;
    void move() override;
    void atualizaHitbox();
    void collider() override;
    void setAlive() override;
};


#endif