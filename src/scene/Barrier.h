#ifndef BARRIER_H
#define BARRIER_H

#include <SFML/Graphics.hpp>
#include "const/Constants.h"

using namespace Obstacle;

class Barrier {
public:
    Barrier();
    int checkCollisionDirection(sf::FloatRect playerRect, sf::Vector2f speed);
    std::vector<sf::FloatRect> getBarrierRects(){return barrierRects;};
    sf::FloatRect getTheOneBarrier(){return theOneBarrier;};

private:
    //存储障碍物矩形
    std::vector<sf::FloatRect> barrierRects = {
        barrier_1
    };
    //正在被碰撞的障碍物
    sf::FloatRect theOneBarrier;
};

#endif