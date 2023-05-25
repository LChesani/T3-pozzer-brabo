#include "GameManager.h"



GameManager::GameManager(int _w, int _h){
    w = _w;
    h = _h;
    player = new Protagonist(w, 50.0, 100.0);
    stage = new Stage(w, h, player);
    fps = new Frames();
    fps->setFps(120.0f);
    currentFps = 120.0f;
    relativeSpeed = 1.0f/120.0f;
    info = new char[100];
}





void GameManager::keyDown(int key){
    if(key == 'a' || key == 'A'){
        player->setDir(0, relativeSpeed);
        return;
    }
    if(key == 'd' || key == 'D'){
        player->setDir(1, relativeSpeed);
        return;
    }
    player->keyPress(key);
}

void GameManager::keyUp(int key){
    player->KeyUp(key);
}

void GameManager::endGame(){
    player = nullptr;
    delete player;
    stage = nullptr;
    delete stage;
}

void GameManager::controlSpeed(){
    player->setSpeedY(400*relativeSpeed);
    stage->s = 400*relativeSpeed;
    player->setSpeed(600*relativeSpeed);
    std::vector<Projectile*> projectiles = player->getCurrentWeapon()->projectiles;
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        (*it)->setSpeed(relativeSpeed);
        it++;
    }

}

void GameManager::fpsControl(){
    currentFps = fps->getFrames();
    relativeSpeed = 1/currentFps;
    controlSpeed();
    CV::color(0,0,0);


    sprintf(info, "FPS: %.0f", currentFps);
    CV::text(10, h-90, info);
    sprintf(info, "Relative Speed: %.5f", relativeSpeed);
    CV::text(10, h-100, info);
}

void GameManager::render(){
    //fps->limit(currentFps); //descomentar caso queira travar o fps, e meio bugado
    fpsControl();
    controlSpeed();
    stage->render();
    player->render();
    player->timeBar(w, h);
    player->hpbar(w, h);
    if(!player->isAlive()){
        endGame();
    }
}
