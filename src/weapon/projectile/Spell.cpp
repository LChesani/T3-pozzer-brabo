#include "Spell.h"

void Spell::atualizaHitbox(){ //garantir que nao vai ter colisao, esse projetil so colide por range
    reta r;
    hitbox.retas.clear();
    r.p1 = Vector2(-900, -900);
    r.p2 = Vector2(-900, -900);
    hitbox.retas.push_back(r);
}


Spell::Spell(int _x, int _y, float _w, float _h){
    sw = _w;
    sh = _h;
    turn = false;
    dim = 40;
    delta = 0;
    speedBase = 200;
    setX(_x+15);
    setY(_y);
    setDamage(9999999); //sim, esse projetil mata tudo
    setSpeed(1/120);
    setHeight(dim);
    setWidth(dim);
    setRange(_h*0.7);
    atualizaHitbox();
    alive = true;
    frameColor = 0;
    n_sprites = 24;
    sprite_count = 0;
    sprites = new Bmp*[24];
    for(int i = 0; i < 24; i++){ //animacao do projetil
        char *path = new char[100];
        sprintf(path, "Trab3LuisChesani/src/assets/projectiles/spell/%d.bmp", i+1);
        sprites[i] = new Bmp(path);
        delete path;
    }
    r = 0;
    g = 0;
    b = 1;
}



void Spell::collider(){

}


void Spell::explosion(){
    reta r;
    setSpeed(0);
    hitbox.retas.clear();
        //retas cobrindo parte da tela, minha colisao depende disso
    for(int i = sh/3; i < sh; i++){
        r.p1 = Vector2(0, i);
        r.p2 = Vector2(sw, i);
        hitbox.retas.push_back(r);
    }
}


void Spell::move(){
    setY(getY() + getSpeed());
    setRange(getRange() - 1);
    if((sound == false) && (getRange() < 100)){
        sound = true;
        playAudio("Trab3LuisChesani/src/assets/projectiles/spell/sounds/0.wav");
    }
    if((getRange() < 10) && (getRange() > 0)){
        speedBase = 0;
        boom = true;
        setRange(9);
        delta+=1;
        r += 0.005;
        b -= 0.005;
        if(delta > 280){
            setRange(0);
            alive = false;
        }
        
        CV::color(r, g, b);
        CV::circleFill(getX(), getY(), sw/3, 50);
        explosion();
    }
}


void Spell::setAlive(){
    
}

void Spell::render(){
    frameColor+=1;
    if(!boom){
        sprites[sprite_count]->draw(getX(), getY());
    } 

    if((frameColor % 5) == 0){
        sprite_count+=1;
    }
    if(sprite_count == (n_sprites-1)){
        sprite_count = 0;
    }
    
}
