#include "Enemy.h"


void Enemy::setHp(int _h){
    hp = _h;
}


void Enemy::atualizaHitbox(){
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

Enemy::Enemy(int _x, int _y, Agent *target, int level){
    setX(_x);
    setY(_y);
    setHeight(40);
    setWidth(40);
    setSpeed(1);
    this->target = target;
    setHp(2*level);

    weapon = new EnemyWeapon(this);

    atualizaHitbox();
}

void Enemy::move(){ //se move em direcao ao alvo
    if (getX() < target->getX()){
        setX(getX() + getSpeed());
    }
    else if (getX() > target->getX()){
        setX(getX() - getSpeed());
    }
    if (getY() < target->getY()){
        setY(getY() + getSpeed());
    }
    else if (getY() > target->getY()){
        setY(getY() - getSpeed());
    }
}


void Enemy::render(){
    move();
    CV::color(0, 1, 0);
    CV::rectFill(getX(), getY(), getX() + getWidth(), getY() + getHeight());
    weapon->render();
    weapon->fire();
    weapon->count+=1;
    atualizaHitbox();
}