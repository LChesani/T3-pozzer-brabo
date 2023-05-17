#include "DefaultProjectile.h"



DefaultProjectile::DefaultProjectile(int _x, int _y){
    setX(_x);
    setY(_y);
    setDamage(1);
    setSpeed(3);
    setHeight(40);
    setWidth(20);
    setRange(300);
}


void DefaultProjectile::move(){
    setY(getY() + getSpeed());
    setRange(getRange() - 1);
}

void DefaultProjectile::render(){
    CV::color(1, 0, 0);
    CV::rectFill(getX(), getY(), getX() + getWidth(), getY() + getHeight());
}
