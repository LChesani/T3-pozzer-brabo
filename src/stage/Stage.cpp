#include "Stage.h"


Stage::Stage(int _w, int _h, Protagonist *player){
    w = _w;
    h = _h;
    ondulation = 500;
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
    std::uniform_int_distribution<> distresq((w*0.08), ondulation);
    std::uniform_int_distribution<> distrdir(w-ondulation, w-(w*0.08));


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



bool isBetween(double value, double start, double end) {
    return value >= start && value <= end;
}

bool getIntersection(const reta& r1, const reta& r2) { //verificar a colisão entre duas retas, algoritmo foi pego da internet, adaptei para os meus dados
    Vector2 intersection;
    double x1 = r1.p1.x, y1 = r1.p1.y;
    double x2 = r1.p2.x, y2 = r1.p2.y;
    double x3 = r2.p1.x, y3 = r2.p1.y;
    double x4 = r2.p2.x, y4 = r2.p2.y;

    double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (denominator == 0) {
        // Retas paralelas, não há interseção
        return false;
    } else {
        double xNumerator = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
        double yNumerator = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

        intersection.x = xNumerator / denominator;
        intersection.y = yNumerator / denominator;

        // Verifica se o ponto de interseção está dentro dos segmentos de reta
        if (isBetween(intersection.x, std::min(r1.p1.x, r1.p2.x), std::max(r1.p1.x, r1.p2.x)) &&
            isBetween(intersection.x, std::min(r2.p1.x, r2.p2.x), std::max(r2.p1.x, r2.p2.x)) &&
            isBetween(intersection.y, std::min(r1.p1.y, r1.p2.y), std::max(r1.p1.y, r1.p2.y)) &&
            isBetween(intersection.y, std::min(r2.p1.y, r2.p2.y), std::max(r2.p1.y, r2.p2.y))) {
            return true;
        } else {
            // Ponto de interseção está fora dos segmentos de reta
            return false;
        }
    }
}



bool Stage::collider() {
    hb hitbox = player->getHitbox();
    for (int i = 0; i < esq.size() - 1; i++) {
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


    if((deltaTime % 1000) == 0){
        enemies.push_back(new Enemy(w/2, h, player, deltaTime/1000));
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

    for(int i = 0; i < esq.size(); i++){
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

    for(auto enemy : enemies){
        enemy->render();
    }

    if(collider()){
        player->reespawn(w);
    }
}