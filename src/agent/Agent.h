#ifndef __AGENT__H__
#define __AGENT__H__

#include "../canvas/gl_canvas2d.h"
#include <vector>
struct reta{
    Vector2 p1;
    Vector2 p2;
};

struct hb{
    std::vector<reta> retas;
};

class Agent{

private:
    int x, y;
    float height, width;
    float speed;
protected:
    int hp;
    hb hitbox;
    Agent *target;
public:
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
    bool collider(Vector2 point) {
        if ((point.x >= getX()) && (point.x <= getX() + getWidth()) && (point.y >= getY()) && (point.y <= getY() + getHeight())) {
            return true;
        }
        return false;
    }
    hb getHitbox() { return hitbox; }
    Agent *getTarget() { return target; }
};












#endif
