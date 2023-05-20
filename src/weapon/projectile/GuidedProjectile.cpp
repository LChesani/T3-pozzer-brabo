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
GuidedProjectile::GuidedProjectile(int _x, int _y, Agent *_target)
{
    setX(_x);
    setY(_y);
    setDamage(1);
    setSpeed(5);
    setHeight(20);
    setWidth(20);
    setRange(300);
    target = _target;
    // direcao
    double directionX = target->getX() - getX();
    double directionY = target->getY() - getY();


    double scalingFactor = getSpeed() / std::sqrt(directionX * directionX + directionY * directionY);
    directionX *= scalingFactor;
    directionY *= scalingFactor;

    // vetor de direcao
    direction = Vector2(directionX, directionY);
    atualizaHitbox();
}

void GuidedProjectile::move()
{
    // atira na direcao
    setX(getX() + direction.x);
    setY(getY() + direction.y);

    setRange(getRange() - 1);
    atualizaHitbox();
}



void GuidedProjectile::render(){
    CV::color(0, 0, 1);
    CV::rectFill(getX(), getY(), getX() + getWidth(), getY() + getHeight());
}
