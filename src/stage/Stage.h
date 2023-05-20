#ifndef __STAGE__H__
#define __STAGE__H__

#include <vector>
#include "../src/agent/Protagonist.h"
#include "../src/canvas/gl_canvas2d.h"
#include "../src/canvas/Vector2.h"
#include "../src/agent/Enemy.h"
#include <random>
#include <chrono>

class Stage{


protected:
    int ondulation;
    Protagonist *player;
    void bezier();
    int w, h;
    float playerY;
    float gap;
    int quadrante;
    float calcGap(int n);
    bool collider();
    int deltaTime;
public:
    Stage(int _w, int _h, Protagonist *player);
    std::vector<Vector2> esq; //pontos que compoe a parede
    std::vector<Vector2> dir; //n quero que as paredes sejam iguais
    std::vector<Enemy*> enemies;
    void render();
    
};

















#endif
