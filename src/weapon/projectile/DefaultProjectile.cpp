#include "DefaultProjectile.h"


void DefaultProjectile::atualizaHitbox(){
    reta r;
    hitbox.retas.clear();
    r.p1 = Vector2(getX(), getY());
    r.p2 = Vector2(getX() + getWidth(), getY());
    hitbox.retas.push_back(r);


    r.p1 = Vector2(getX(), getY() + getHeight());
    r.p2 = Vector2(getX() + getWidth(), getY() + getHeight());
    hitbox.retas.push_back(r);

    r.p1 = Vector2(getX(), getY());
    r.p2 = Vector2(getX(), getY() + getHeight());
    hitbox.retas.push_back(r);

    r.p1 = Vector2(getX() + getWidth(), getY());
    r.p2 = Vector2(getX() + getWidth(), getY() + getHeight());
    hitbox.retas.push_back(r);
    
}

void DefaultProjectile::collider(){

}


DefaultProjectile::DefaultProjectile(int _x, int _y){
    setX(_x);
    setY(_y);
    setDamage(1);
    setSpeed(20);
    setHeight(40);
    setWidth(20);
    setRange(300);
    atualizaHitbox();
    alive = true;
}


void DefaultProjectile::move(){
    setY(getY() + getSpeed());
    setRange(getRange() - 1);
    atualizaHitbox();
}

void DefaultProjectile::render(){
    CV::color(1, 0, 0);
    CV::rectFill(getX(), getY(), getX() + getWidth(), getY() + getHeight());
}
