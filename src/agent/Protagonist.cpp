#include "Protagonist.h"
#include "../weapon/Weapon.h"

Protagonist::Protagonist(int _w, float width, float height){
    setSpeedY(10); //cima
    setSpeed(8); //lados
    setX(_w/2 - width/2);
    setY(0);
    setWidth(width);
    setHeight(height);
    base = new Base(this);
    setFiring(false);
    setCurrentWeapon(base);
    for(int i = 0; i < 2; i++){
        dir[i] = 0;
    }
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
        setFiring(true);
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



void Protagonist::shoot(){
    getCurrentWeapon()->fire();
}


void Protagonist::render(){
    move();
    CV::color(0, 0, 0);
    CV::rectFill(getX(), getY(), getX() + getWidth(), getY() + getHeight());
    base->count+=1;
    if(getFiring()){
        shoot();
    }


    base->render();
    //special->render();
}
