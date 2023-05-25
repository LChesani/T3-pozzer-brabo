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
    score = 0;
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

    player->getCurrentWeapon()->setCooldown(relativeSpeed);

    for(auto it = stage->enemies.begin(); it != stage->enemies.end();){
        for(auto it2 = (*it)->weapon->projectiles.begin(); it2 != (*it)->weapon->projectiles.end();){
            (*it2)->setSpeed(relativeSpeed);
            it2++;
        }
        (*it)->setRelativeSpeed(relativeSpeed);
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

void GameManager::plotScore(){
    CV::color(1, 1, 1);
    sprintf(info, "%d", score);
    CV::text(w/2-(10*strlen(info)), h-10, info);
}

void GameManager::hud(){
    CV::color(0);
    CV::rectFill(0, h, w, h-37);
    CV::color(1, 1, 1);
    CV::rectFill(5, h-5, 205, h-32);
    plotScore();
    player->timeBar(w, h);
    player->hpbar(w, h);
}

void GameManager::render(){
    //fps->limit(currentFps); //descomentar caso queira travar o fps, e meio bugado, so fiz pra teste
    fpsControl();
    controlSpeed();
    stage->render();
    score = stage->score;
    player->render();
    if(!player->isAlive()){
        endGame();
    }
    hud();
}
