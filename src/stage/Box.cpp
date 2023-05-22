#include "Box.h"


void Box::atualizaHitbox(){
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


Box::Box(float _x, float _y, Protagonist *_user, float _w, float _h){
    sw = _w;
    sh = _h;
    x = _x;
    y = _y;
    w = 100;
    h = 100;
    std::random_device rd;
    std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> weap(0, possible_weapons-1); //escolhe uma das armas especiais possiveis
 
    id = weap(eng);
    char numero = id+48;

    char *path = new char[100];

    sprintf(path, "Trab3 (malvado)/src/assets/boxes/%d.bmp", id);
    sprite = new Bmp(path);
    user = _user;
    atualizaHitbox();
}


void Box::selectWeapon(){
    if(id == 0){
        user->special = new Glock(user);
        return;
    }
    if(id == 1){
        user->special = new Staff(user, sw, sh);
        return;
    }
}

void Box::collider(){
    for(auto r : user->getHitbox().retas){
        for(auto r2 : hitbox.retas){
            if(getIntersection(r, r2)){
                selectWeapon();
                alive = false;
                return;
            }
        }
    }
}


void Box::render(){
    atualizaHitbox();
    collider();
    sprite->draw(getX(), getY());
}