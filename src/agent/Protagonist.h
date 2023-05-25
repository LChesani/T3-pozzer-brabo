#ifndef __PROTAGONIST__H__
#define __PROTAGONIST__H__

#include "Agent.h"
#include "../weapon/Weapon.h"
#include "../weapon/Base.h"
#include "../weapon/Glock.h"



class Protagonist : public Agent{

private:
    Weapon *current; //ponteiro para a arma atual
    bool firing;
    float speedy;

protected:
    int imortal;
    int timer; //tempo que pode usar a arma especial
    void status();
    Bmp *healthBar;
    float dir[2]; //direções
public:
    Weapon *base;
    Weapon *special;
    Protagonist(int _w, float width, float height);
    void render() override;
    void move() override;
    void keyPress(int key);
    void KeyUp(int key);
    void setFiring(bool _f) { firing = _f; }
    bool getFiring() { return firing; }
    Weapon *getCurrentWeapon() { return current; }
    void setCurrentWeapon(Weapon *_c) { current = _c; }
    void shoot();
    void setSpeedY(int _s) { speedy = _s; }
    float getSpeedY(){ return speedy; }
    void atualizaHitbox();
    void reespawn(float sw);
    bool isAlive();
    void setHp(int _h) override;
    void powerUp(Weapon *_new);
    void timeBar(float _w, float _h);
    void hpbar(int _w, int _h);
    void setDir(int _dir, float relativeSpeed);
};











#endif
