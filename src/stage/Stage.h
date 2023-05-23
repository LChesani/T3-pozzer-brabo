#ifndef __STAGE__H__
#define __STAGE__H__

#include <vector>
#include "../src/canvas/Vector2.h"
#include "../src/agent/Enemy.h"
#include "Box.h"

class Stage{


protected:
    int ondulation;
    void bezier();
    int w, h;
    float playerY;
    float gap;
    int quadrante;
    float calcGap(int n);
    bool collider();
    int deltaTime;
public:
    std::vector<Box*> boxes;
    Protagonist *player;
    Stage(int _w, int _h, Protagonist *player);
    std::vector<Vector2> esq; //pontos que compoe a parede
    std::vector<Vector2> dir; //n quero que as paredes sejam iguais
    std::vector<Enemy*> enemies;
    void render();
    
};

















#endif
