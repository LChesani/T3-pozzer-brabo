#ifndef __AGENT__H__
#define __AGENT__H__

#include "../canvas/Frames.h"

#include <vector>


class Agent{

private:
    float x, y;
    float height, width;
protected:
    int hp;
    hb hitbox;
    Agent *target;
    float speed;
public:
    Bmp **sprites;
    int n_sprites;
    int sprite_count;
    int delta;
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
    void setSpeed(float _s) { speed = _s; }
    float getSpeed() { return speed; }
    virtual void setHp(int _h) = 0;
    int getHp() { return hp; }
    hb getHitbox() { return hitbox; }
    Agent *getTarget() { return target; }
};











#endif
