#ifndef __ENEMY__H__
#define __ENEMY__H__

#include "../agent/Agent.h"
#include "../weapon/Weapon.h"
#include "../weapon/EnemyWeapon.h"


class Enemy : public Agent{


protected:
    float speedBase;
public:
    Weapon *weapon;
    bool alive;
    Enemy(int _x, int _y, Agent *target, int level);
    void render() override;
    void move() override;
    void setHp(int _h) override;
    void atualizaHitbox();
    void collider();
    void update(Weapon *_w);
    void setRelativeSpeed(float relativeSpeed) { speed = speedBase*relativeSpeed; }
};



#endif
