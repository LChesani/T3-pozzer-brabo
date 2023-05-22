#ifndef __BOX__H__
#define __BOX__H__
#include <random>
#include <chrono>
#include "../weapon/Weapon.h"
#include "../weapon/Glock.h"
#include "../weapon/Staff.h"
#include "../agent/Protagonist.h"






class Box{

private:
    float x, y;
    float w, h;
    float sw, sh;

protected:
    Protagonist *user;
    int possible_weapons = 2;
public:
    bool alive = true;
    int id; //numero da arma
    Box(float _x, float _y, Protagonist *_user, float _w, float _h);
    hb hitbox;
    Bmp *sprite;
    float getX() { return x; }
    float getY() { return y; }
    void setX(float _x) { x = _x;}
    void setY(float _y) { y = _y;}
    float getHeight() { return h; }
    float getWidth() { return w; }
    void setHeight(float _h) { h = _h;}
    void setWidth(float _w) { w = _w;}
    void atualizaHitbox();
    void selectWeapon();
    void collider();
    void render();
};













#endif