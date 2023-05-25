#ifndef _GAMEMANAGER__H__
#define _GAMEMANAGER__H__


#include "canvas/utils.h"
#include "agent/Protagonist.h"
#include "stage/Stage.h"



class GameManager{

protected:
    Protagonist *player;
    Stage *stage;
    Frames *fps;
    int w, h;
    float relativeSpeed;
    float currentFps;
    char *info;
public:
    GameManager(int _w, int _h);
    void render();
    void keyUp(int key);
    void keyDown(int key);
    void endGame();
    void fpsControl();
    void controlSpeed();
};

















#endif