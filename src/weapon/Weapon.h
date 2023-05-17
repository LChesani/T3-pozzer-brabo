#ifndef __WEAPON__H__
#define __WEAPON__H__

#include "../canvas/gl_canvas2d.h"
#include "projectile/Projectile.h"
#include "../agent/Agent.h"
#include <vector>




class Weapon{


private:
    Projectile *p;
    Agent *user;

protected:
    std::vector<Projectile*> projectiles;
    
    
public:
    Projectile *getProjectile() { return p; }
    int count;
    int cooldown;
    void setProjectile(Projectile *_p) { p = _p; }
    virtual void fire() = 0;
    Agent *getUser() { return user; }
    void setUser(Agent *_u) { user = _u; }
    void render(){
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            if ((*it)->getRange() <= 0) {
                delete *it; // Deletar o objeto apontado pelo ponteiro
                it = projectiles.erase(it); // Remover o ponteiro do vetor e atualizar o iterador
            } else {
                (*it)->render(); // Chamar o método render() no objeto apontado pelo ponteiro
                (*it)->move(); // Chamar o método move() no objeto apontado pelo ponteiro
                ++it; // Incrementar o iterador para avançar para o próximo elemento
            }
        }
    }
};















#endif
