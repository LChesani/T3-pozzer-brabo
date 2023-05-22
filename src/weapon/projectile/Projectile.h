#ifndef __PROJECTILE__H__
#define __PROJECTILE__H__


#include "../../canvas/gl_canvas2d.h"
#include "../../agent/Agent.h"
#include "../src/canvas/utils.h"



class Projectile{


private:
    float x, y;
    float height, width;
    float speed;
    int damage;
    int range; //alcance
protected:
    

public:
    Bmp **sprites;
    int n_sprites;
    int sprite_count;
    int delta;
    
    hb hitbox;
    bool alive; //se a bala ainda ta no jogo
    float getX() { return x; }
    float getY() { return y; }
    void setX(float _x) { x = _x;}
    void setY(float _y) { y = _y;}
    float getHeight() { return height; }
    float getWidth() { return width; }
    void setHeight(float _h) { height = _h;}
    void setWidth(float _w) { width = _w;}
    virtual void render() = 0;
    virtual void move() = 0;
    void setSpeed(int _s) { speed = _s; }
    float getSpeed() { return speed; }
    int getDamage() { return damage; }
    void setDamage(int _d) { damage = _d; }
    int getRange() { return range; }
    void setRange(int _r) { range = _r; }
    virtual void collider() = 0;
    virtual void setAlive() = 0;
};



#endif
