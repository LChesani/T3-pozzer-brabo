#include "Protagonist.h"
#include "../weapon/Weapon.h"

Protagonist::Protagonist(int _w, float width, float height){
    setX(_w/2 - width/2);
    setY(50);
    setWidth(width);
    setHeight(height);
    setSpeed(2);
    base = new Base(this);
    setCurrentWeapon(base);
    for(int i = 0; i < 4; i++){
        dir[i] = 0;
    }
}

void Protagonist::move(){
    setX(getX() + getSpeed() * (dir[0] + dir[1]));
    setY(getY() + getSpeed() * (dir[2] + dir[3]));
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
    if(key == 'w' || key == 'W'){
        dir[2] = 1;
        return;
    }
    if(key == 's' || key == 'S'){
        dir[3] = -1;
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
    if(key == 'w' || key == 'W'){
        dir[2] = 0;
        return;
    }
    if(key == 's' || key == 'S'){
        dir[3] = 0;
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
