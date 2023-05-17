#ifndef __PROJECTILE__H__
#define __PROJECTILE__H__


#include "../../canvas/gl_canvas2d.h"
#include "../../agent/Agent.h"





class Projectile{


private:
    int x, y;
    float height, width;
    int speed;
    int damage;
    int range; //alcance

public:
    int getX() { return x; }
    int getY() { return y; }
    void setX(float _x) { x = _x;}
    void setY(float _y) { y = _y;}
    float getHeight() { return height; }
    float getWidth() { return width; }
    void setHeight(float _h) { height = _h;}
    void setWidth(float _w) { width = _w;}
    virtual void render() = 0;
    virtual void move() = 0;
    void setSpeed(int _s) { speed = _s; }
    int getSpeed() { return speed; }
    int getDamage() { return damage; }
    void setDamage(int _d) { damage = _d; }
    int getRange() { return range; }
    void setRange(int _r) { range = _r; }
};



#endif
