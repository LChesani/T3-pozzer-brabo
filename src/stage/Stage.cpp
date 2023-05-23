#include "Stage.h"





Stage::Stage(int _w, int _h, Protagonist *player){
    w = _w;
    h = _h;
    ondulation = 200;
    gap = h/3; //tamanho de cada quadrante da tela, cada ponto de controle vai ficar em 1 terco da tela
    this->player = player;
    for(int i = 0; i < 4; i++){ //inicializando como uma curva reta
        esq.push_back(Vector2(ondulation, gap*i));
        dir.push_back(Vector2(w-ondulation, gap*i));
    }
    playerY = player->getY();
    bezier();
    quadrante = 0;
    deltaTime = 0; //famoso delta time calculado por frame
}

float Stage::calcGap(int n){
    return gap*n;
}

void Stage::bezier(){ //gera pontos de bezier para serem usados em uma curva cúbica
    std::random_device rd;
    std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count()/7);
    std::uniform_int_distribution<> distresq((w*0.05), ondulation);
    std::uniform_int_distribution<> distrdir(w-ondulation, w-(w*0.05));


    std::vector<Vector2> esq_copy = esq;
    std::vector<Vector2> dir_copy = dir;
    float diff;

    diff = 2*esq[esq_copy.size()-1].x - esq[esq_copy.size()-2].x;

    float _ini = esq_copy[esq_copy.size()-1].y;

    esq.push_back(Vector2(esq_copy[esq_copy.size()-1].x, _ini+calcGap(0))); //ponto em comum
    esq.push_back(Vector2(diff, _ini+calcGap(1))); //garantir a inclinação
    esq.push_back(Vector2(distresq(eng), _ini+calcGap(2)));
    esq.push_back(Vector2(distresq(eng), _ini+calcGap(3)));

    std::mt19937 eng2(std::chrono::high_resolution_clock::now().time_since_epoch().count()/3);

    diff = 2*dir_copy[dir_copy.size()-1].x - dir_copy[dir_copy.size()-2].x;

    dir.push_back(Vector2(dir_copy[dir_copy.size()-1].x, _ini+calcGap(0)));
    dir.push_back(Vector2(diff, _ini+calcGap(1)));
    dir.push_back(Vector2(distrdir(eng2), _ini+calcGap(2)));
    dir.push_back(Vector2(distrdir(eng2), _ini+calcGap(3)));
}


void fazPonto(float x, float y){
    CV::color(0);
    for(int i = 0; i < 10; i++){
        CV::point(x+i, y+i);
    }
}

void removeAntigos(std::vector<Vector2> &v){
    if(v.size() > 12){
        v.erase(v.begin(), v.begin()+4);
    }
}




bool Stage::collider() {
    hb hitbox = player->getHitbox();
    for (unsigned int i = 0; i < esq.size() - 1; i++) {
        for (int j = 0; j < player->getHitbox().retas.size(); j++) {
            reta r;
            r.p1 = esq[i];
            r.p2 = esq[i + 1];
            if (getIntersection(r, hitbox.retas[j])) {
                return true;
            }
            r.p1 = dir[i];
            r.p2 = dir[i + 1];
            if (getIntersection(r, hitbox.retas[j])) {
                return true;
            }
        }
    }
    return false; // Nenhuma interseção encontrada
}




void Stage::render(){
    deltaTime += 1;


    if(player == nullptr){
        return;
    }


    if((deltaTime % 500) == 0){
        enemies.push_back(new Enemy(w/2, h, player, deltaTime/1000));
    }

    if((deltaTime % 1500) == 0){
        std::random_device rd;
        std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> local(w*0.1, w-(w*0.1));
        boxes.push_back(new Box(local(eng), h, player, w, h));
    }



    int s = player->getSpeedY();

    int _quadr = (static_cast<int>(playerY) / static_cast<int>(gap))/3;


    if(_quadr > quadrante){
        bezier();
        quadrante = _quadr;
        removeAntigos(esq);
        removeAntigos(dir);
    }

    float xe, ye, xd, yd;



    playerY += s;

    for(unsigned int i = 0; i < esq.size(); i++){
        esq[i].y -= s;
        dir[i].y -= s;


        if((i%4) == 0){
            for(float t = 0; t <= 1; t += 0.002){
                xe = pow(1-t, 3)*esq[i].x + 3*t*pow(1-t, 2)*esq[i+1].x + 3*pow(t, 2)*(1-t)*esq[i+2].x + pow(t, 3)*esq[i+3].x;
                ye = pow(1-t, 3)*esq[i].y + 3*t*pow(1-t, 2)*esq[i+1].y + 3*pow(t, 2)*(1-t)*esq[i+2].y + pow(t, 3)*esq[i+3].y;
                xd = pow(1-t, 3)*dir[i].x + 3*t*pow(1-t, 2)*dir[i+1].x + 3*pow(t, 2)*(1-t)*dir[i+2].x + pow(t, 3)*dir[i+3].x;
                yd = pow(1-t, 3)*dir[i].y + 3*t*pow(1-t, 2)*dir[i+1].y + 3*pow(t, 2)*(1-t)*dir[i+2].y + pow(t, 3)*dir[i+3].y;
                fazPonto(xe, ye);
                fazPonto(xd, yd);
            }
        }
    }

    for (auto it = enemies.begin(); it != enemies.end();) {
        if (!(*it)->alive) {
            delete *it; // Deletar o objeto apontado pelo ponteiro
            it = enemies.erase(it); // Remover o ponteiro do vetor e atualizar o iterador
        } else {
            (*it)->update(player->getCurrentWeapon()); //verifica se alguma bala pegou nele
            (*it)->render(); // Chamar o método render() no objeto apontado pelo ponteiro
            ++it; // Incrementar o iterador para avançar para o próximo elemento
        }
    }

    for (auto it = boxes.begin(); it != boxes.end();) {
        if (!(*it)->alive || ((*it)->getY() < 0)) {
            delete *it; // Deletar o objeto apontado pelo ponteiro
            it = boxes.erase(it); // Remover o ponteiro do vetor e atualizar o iterador
        } else {
            (*it)->setY((*it)->getY()-0.5);
            (*it)->render(); // Chamar o método render() no objeto apontado pelo ponteiro
            ++it; // Incrementar o iterador para avançar para o próximo elemento
        }
    }

    if(collider()){
        player->reespawn(w);
    }
}
