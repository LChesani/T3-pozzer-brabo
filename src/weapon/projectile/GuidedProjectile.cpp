#include "GuidedProjectile.h"



void GuidedProjectile::atualizaHitbox(){
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


void GuidedProjectile::collider(){
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

void GuidedProjectile::setAlive(){
    alive = false;
}


GuidedProjectile::GuidedProjectile(int _x, int _y, Agent *_target)
{
    setX(_x);
    setY(_y-50);
    setDamage(1);
    setSpeed(5);
    setHeight(20);
    setWidth(20);
    setRange(150);
    target = _target;
    // direcao
    double directionX = target->getX() - getX();
    double directionY = target->getY() - getY();


    double scalingFactor = getSpeed() / std::sqrt(directionX * directionX + directionY * directionY);
    directionX *= scalingFactor;
    directionY *= scalingFactor;

    // vetor de direcao
    direction = Vector2(directionX, directionY);
    alive = true;
    atualizaHitbox();
    delta = 0;
    n_sprites = 11;
    sprite_count = 0;
    sprites = new Bmp*[11];
    sprites[0] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/1.bmp");
    sprites[1] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/2.bmp");
    sprites[2] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/3.bmp");
    sprites[3] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/4.bmp");
    sprites[4] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/5.bmp");
    sprites[5] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/6.bmp");
    sprites[6] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/7.bmp");
    sprites[7] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/8.bmp");
    sprites[8] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/9.bmp");
    sprites[9] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/10.bmp");
    sprites[10] = new Bmp("Trab3 (malvado)/src/assets/projectiles/guided/11.bmp");
}

void GuidedProjectile::move()
{
    // atira na direcao
    setX(getX() + direction.x);
    setY(getY() + direction.y);

    setRange(getRange() - 1);
    atualizaHitbox();
    collider();
}



void GuidedProjectile::render(){
    sprites[sprite_count]->draw(getX(), getY());
    delta++;
    if((delta % 10) == 0){
        sprite_count+=1;
    }
    if(sprite_count == (n_sprites-1)){
        sprite_count = 0;
    }
}
