#include "Stage.h"
#include <random>
#include <chrono>

Stage::Stage(int _w, int _h, Protagonist *player){
    w = _w;
    h = _h;
    ondulation = 150;
    gap = h/3; //tamanho de cada quadrante da tela, espaço delimitado pelas curvas e serve para auxiliar no controle de renderizacao
    this->player = player;
    for(int i = 0; i < 4; i++){ //inicializando como uma curva reta
        esq.push_back(Vector2(ondulation, gap*i));
        dir.push_back(Vector2(w-ondulation, gap*i));
    }
    playerY = player->getY();
    bezier(0);
    quadrante = 0;
}

void Stage::bezier(float ini){ //gera pontos de bezier para serem usados em uma curva cúbica
    std::random_device rd;
    std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> distresq(25, ondulation);
    std::uniform_int_distribution<> distrdir(w-ondulation, w-25);


    std::vector<Vector2> esq_copy = esq;
    std::vector<Vector2> dir_copy = dir;
    float diff;
    diff = 2*esq[esq_copy.size()-1].x - esq_copy[esq_copy.size()-2].x;

    esq.push_back(Vector2(esq_copy[esq_copy.size()-1].x, ini+gap*0)); //ponto em comum
    esq.push_back(Vector2(diff, ini+gap*1)); //garantir a inclinação
    esq.push_back(Vector2(distresq(eng), ini+gap*2));
    esq.push_back(Vector2(distresq(eng), ini+gap*3));

    std::mt19937 eng2(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    diff = 2*dir_copy[dir_copy.size()-1].x - dir_copy[dir_copy.size()-2].x;

    dir.push_back(Vector2(dir_copy[dir_copy.size()-1].x, ini+gap*0));
    dir.push_back(Vector2(diff, ini+gap*1));
    dir.push_back(Vector2(distrdir(eng2), ini+gap*2));
    dir.push_back(Vector2(distrdir(eng2), ini+gap*3));
    if(first_time){
        first_time = false;
        esq.erase(esq.begin(), esq.begin()+4);
        dir.erase(dir.begin(), dir.begin()+4);
    }

}


void Stage::render(){
    CV::color(0);
    int s = player->getSpeedY();

    int _quadr = (static_cast<int>(playerY) / static_cast<int>(gap));

    printf("%d\n", esq.size());

    if(_quadr > quadrante){
        bezier(_quadr*gap*2);
        quadrante = _quadr;
    }

    float xp, yp;


    playerY += s;

    for(int i = 0; i < esq.size(); i++){
        esq[i].y -= s;
        dir[i].y -= s;

        if((i%4) == 0){
            for(float t = 0; t <= 1; t += 0.005){
                xp = pow(1-t, 3)*esq[i].x + 3*t*pow(1-t, 2)*esq[i+1].x + 3*pow(t, 2)*(1-t)*esq[i+2].x + pow(t, 3)*esq[i+3].x;
                yp = pow(1-t, 3)*esq[i].y + 3*t*pow(1-t, 2)*esq[i+1].y + 3*pow(t, 2)*(1-t)*esq[i+2].y + pow(t, 3)*esq[i+3].y;
                CV::point(xp, yp);
                xp = pow(1-t, 3)*dir[i].x + 3*t*pow(1-t, 2)*dir[i+1].x + 3*pow(t, 2)*(1-t)*dir[i+2].x + pow(t, 3)*dir[i+3].x;
                yp = pow(1-t, 3)*dir[i].y + 3*t*pow(1-t, 2)*dir[i+1].y + 3*pow(t, 2)*(1-t)*dir[i+2].y + pow(t, 3)*dir[i+3].y;
                CV::point(xp, yp);
            }
            
        }
    }
}
