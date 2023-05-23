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
    setSpeed(0.25);
    this->target = target;
    setHp(2*level);
    alive = true;
    weapon = new EnemyWeapon(this);

    atualizaHitbox();
    delta = 0;
    n_sprites = 8;
    sprite_count = 0;
    sprites = new Bmp*[8];
    sprites[0] = new Bmp("Trab3 (malvado)/src/assets/enemies/1.bmp");
    sprites[1] = new Bmp("Trab3 (malvado)/src/assets/enemies/2.bmp");
    sprites[2] = new Bmp("Trab3 (malvado)/src/assets/enemies/3.bmp");
    sprites[3] = new Bmp("Trab3 (malvado)/src/assets/enemies/4.bmp");
    sprites[4] = new Bmp("Trab3 (malvado)/src/assets/enemies/5.bmp");
    sprites[5] = new Bmp("Trab3 (malvado)/src/assets/enemies/6.bmp");
    sprites[6] = new Bmp("Trab3 (malvado)/src/assets/enemies/7.bmp");
    sprites[7] = new Bmp("Trab3 (malvado)/src/assets/enemies/8.bmp");
}

void Enemy::move(){ //se move em direcao ao alvo
    if (getX() < target->getX()){
        setX(getX() + getSpeed());
    }
    else if (getX() > target->getX()){
        setX(getX() - getSpeed());
    }

    if (getY() > target->getY()){
        setY(getY() - getSpeed());
    }
}


void Enemy::update(Weapon *_w){
    for (auto it = _w->projectiles.begin(); it != _w->projectiles.end(); ++it) {
        for(auto r2 : hitbox.retas){
            for(auto r3 : (*it)->hitbox.retas){
                if(getIntersection(r2, r3)){
                    setHp(getHp() - (*it)->getDamage()); //dano ao contato
                    (*it)->setAlive();
                }
            }
        }
    }
}

void Enemy::collider(){
    for(auto r : target->getHitbox().retas){
        for(auto r2 : hitbox.retas){
            if(getIntersection(r, r2)){
                target->setHp(target->getHp() - 1); //dano ao contato
                alive = false;
                return;
            }
        }
    }
}

void Enemy::render(){
    delta += 1;
    move();
    if(getHp() <= 0){
        alive = false;
    }

    if((delta % 25) == 0){
        sprite_count+=1;
    }

    weapon->render();
    weapon->fire();
    weapon->count+=1;
    atualizaHitbox();
    collider();
    if(sprite_count == 8){
        sprite_count = 0;
    }
    sprites[sprite_count]->draw(getX(), getY());
}