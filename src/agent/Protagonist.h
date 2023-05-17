#ifndef __PROTAGONIST__H__
#define __PROTAGONIST__H__
#include "Agent.h"
#include "../weapon/Weapon.h"
#include "../weapon/Base.h"

class Protagonist : public Agent{

private:
    Weapon *current; //ponteiro para a arma atual
    bool firing;

protected:
    Weapon *base;
    Weapon *special;
    int dir[4]; //direções
public:
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
    void limit();
};











#endif
