#include "Protagonist.h"
#include "../weapon/Weapon.h"

void Protagonist::atualizaHitbox() {
    hitbox.retas.clear();

    Vector2 p1(getX(), getY());
    Vector2 p2(getX() + getWidth(), getY());
    Vector2 p3(getX() + getWidth() / 2, getY() + getHeight());

    reta r1;
    r1.p1 = p1;
    r1.p2 = p2;
    hitbox.retas.push_back(r1);

    reta r2;
    r2.p1 = p2;
    r2.p2 = p3;
    hitbox.retas.push_back(r2);

    reta r3;
    r3.p1 = p3;
    r3.p2 = p1;
    hitbox.retas.push_back(r3);
}


Protagonist::Protagonist(int _w, float width, float height){
    target = nullptr;
    setSpeedY(2); //cima
    setSpeed(8); //lados
    setX(_w/2 - width/2);
    setY(10);
    setHp(3); //vida
    setWidth(width);
    setHeight(height);
    base = new Base(this);
    setFiring(false);
    setCurrentWeapon(base);
    for(int i = 0; i < 2; i++){
        dir[i] = 0;
    }

    imortal = 0;

    atualizaHitbox();
    color = 0;

}




void Protagonist::move(){
    setX(getX() + getSpeed() * (dir[0] + dir[1]));
}

void Protagonist::keyPress(int key){
    
    if(key == 'a' || key == 'A'){
        dir[0] = -1;
        return;
    }
    if(key == 'd' || key == 'D'){
        dir[1] = 1;
        return;
    }
    if(key == '1'){
        setCurrentWeapon(base);
        return;
    }
    if(key == '2'){
        setCurrentWeapon(special);
        return;
    }
    if(key == ' '){
        if(imortal <= 0){ //se esta com status de imortal nao pode atirar
            setFiring(true);
        }
        return;
    }
}

void Protagonist::KeyUp(int key){
    if(key == ' '){
        setFiring(false);
        return;
    }
    if(key == 'a' || key == 'A'){
        dir[0] = 0;
        return;
    }
    if(key == 'd' || key == 'D'){
        dir[1] = 0;
        return;
    }
}

void Protagonist::setHp(int _h){
    if(imortal == 0){ //se esta com status de imortal nao pode perder nem recuperar vida
        hp = _h;
        imortal = 200; //tempo imortal devido a reespawnar
    }
}

void Protagonist::shoot(){
    getCurrentWeapon()->fire();
}

void Protagonist::reespawn(float sw){
    setHp(getHp() - 1);
    setX(sw/2);
}

void Protagonist::status(){
    if(imortal > 0){
        imortal-=1;
        if(imortal % 25 == 0){ //pisca pisca
            if(color == 0){
                color = 13;
            }
            else{
                color = 0;
            }
        }
    }
}

bool Protagonist::isAlive(){
    return getHp() > 0;
}

void Protagonist::render(){
    move();
    status();
    CV::color(color);
    isAlive();

    float vx[] = { getX(), getX() + getWidth(), getX() + getWidth() / 2 };
    float vy[] = { getY(), getY(), getY() + getHeight() };

    CV::polygonFill(vx, vy, 3);

    base->count+=1;
    if(getFiring()){
        shoot();
    }

    atualizaHitbox();
    base->render();
    //special->render();
}
