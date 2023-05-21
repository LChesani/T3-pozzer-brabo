#ifndef __UTILS__H__
#define __UTILS__H__
#include <cmath>
#include <vector>
#include "Vector2.h"
#include "../bmp/Bmp.h"

struct reta{
    Vector2 p1;
    Vector2 p2;
};

struct hb{
    std::vector<reta> retas;
};

static bool isBetween(double value, double start, double end) {
    return value >= start && value <= end;
}

static bool getIntersection(const reta& r1, const reta& r2) { //verificar a colisão entre duas retas, algoritmo foi pego da internet, adaptei para os meus dados
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


#endif