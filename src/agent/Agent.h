#ifndef __AGENT__H__
#define __AGENT__H__

#include "../canvas/gl_canvas2d.h"



class Agent{

private:
    int x, y;
    float height, width;
    int speed;

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
};












#endif
