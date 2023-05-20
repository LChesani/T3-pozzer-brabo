#ifndef __STAGE__H__
#define __STAGE__H__

#include <vector>
#include <../src/agent/Protagonist.h>
#include <../src/canvas/gl_canvas2d.h>
#include <../src/canvas/Vector2.h>

class Stage{


protected:
    bool first_time = true;
    int ondulation;
    Protagonist *player;
    void bezier(float ini);
    void colision();
    int w, h;
    float playerY;
    float gap;
    int quadrante;
public:
    Stage(int _w, int _h, Protagonist *player);
    std::vector<Vector2> esq; //pontos que compoe a parede
    std::vector<Vector2> dir; //pontos que compoe a parede //n quero que as paredes sejam iguais
    void render();
};

















#endif
