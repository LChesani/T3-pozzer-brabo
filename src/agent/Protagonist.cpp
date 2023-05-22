#include "Protagonist.h"


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
    setSpeed(4); //lados
    setX(_w/2 - width/2);
    setY(10);
    setHp(3); //vida
    setWidth(width);
    setHeight(height);
    base = new Base(this);
    special = nullptr;
    setFiring(false);
    setCurrentWeapon(base);
    for(int i = 0; i < 2; i++){
        dir[i] = 0;
    }

    imortal = 0;

    delta = 0;

    atualizaHitbox();
    timer = 0;
    n_sprites = 4;
    sprite_count = 0;
    sprites = new Bmp*[4];
    sprites[0] = new Bmp("Trab3 (malvado)/src/assets/protagonist/1.bmp");
    sprites[1] = new Bmp("Trab3 (malvado)/src/assets/protagonist/2.bmp");
    sprites[2] = new Bmp("Trab3 (malvado)/src/assets/protagonist/3.bmp");
    sprites[4] = new Bmp("Trab3 (malvado)/src/assets/protagonist/4.bmp");
    healthBar = new Bmp("Trab3 (malvado)/src/assets/protagonist/life.bmp");
}



void Protagonist::timeBar(float _w, float _h){
    if(timer > 0){
        timer--;
        if(timer == 0){
            setCurrentWeapon(base);
            special = nullptr;
        }
        CV::color(0, 0, 0);
        for(int i = 0; i < 10; i++){
            CV::rect(0+i, _h-i, 200+i, _h-50+i);
        }
        int progress = timer/10;
        
        float r = 1;
        float g = 0;
        float b = 0;

        for(int i = 0; i < progress; i++){
            g += 1.0f/200.0f;
            r -= 1.0f/200.0f;
            CV::color(r, g, b);
            CV::line(i+10, _h-10, i+10, _h-40);
        }
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
        special = nullptr;
        timer = 0;
        return;
    }
    if(key == '2'){
        if(special != nullptr && (getCurrentWeapon() != special)){
            timer = 2000;
            setCurrentWeapon(special);
        }
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
        CV::color(0, 1, 1);
        for(int i = 0; i < 5; i++){
            CV::circle(getX() + getWidth()/2-4, getY() + getHeight()/2-10, getWidth()+i, 200);
        }
    }

    
}

bool Protagonist::isAlive(){
    return getHp() > 0;
}

void Protagonist::hpbar(int _w, int _h){
    float __h = healthBar->getHeight();
    float __w = healthBar->getWidth();
    for(int i = 0; i < getHp(); i++){
        healthBar->draw(_w - (i+1)*__w, _h-__h);
    }
}


void Protagonist::powerUp(Weapon *_new){
    special = _new;
}

void Protagonist::render(){
    move();
    status();
    
    isAlive();


    current->count+=1;
    if(getFiring()){
        shoot();
    }

    atualizaHitbox();

    current->render();


    sprites[sprite_count]->draw(getX(), getY());
    delta++;
    if((delta % 25) == 0){
        sprite_count+=1;
    }
    if(sprite_count == (n_sprites-1)){
        sprite_count = 0;
    }
}
