#include "RainbowProjectile.h"


void RainbowProjectile::atualizaHitbox(){
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

void RainbowProjectile::collider(){

}


RainbowProjectile::RainbowProjectile(int _x, int _y){
    speedBase = 4000;
    turn = false;
    setX(_x+15);
    setY(_y);
    setDamage(2);
    setSpeed(1/120);
    setHeight(20);
    setWidth(20);
    setRange(50);
    atualizaHitbox();
    alive = true;
}




void RainbowProjectile::move(){
    setY(getY() + getSpeed());
    setRange(getRange() - 1);
    atualizaHitbox();
}


void RainbowProjectile::setAlive(){
    alive = false;
}

void RainbowProjectile::render(){
    if(turn){
        CV::color(0, 1, 1);
        setX(getX() + 30);
    }
    else{
        CV::color(1, 1, 0);
        setX(getX() - 30);
    }
    turn = !turn;
    
    CV::rectFill(getX(), getY(), getX() + getWidth(), getY() + getHeight());

    CV::color(0, 0, 0);
    for(int i = 0; i < 5; i++){
        CV::rect(getX()-i, getY()-i, getX() + getWidth()+i, getY() + getHeight()+i);
    }
}
