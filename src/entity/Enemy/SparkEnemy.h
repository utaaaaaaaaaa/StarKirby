#ifndef SPARK_ENEMY_H
#define SPARK_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"

class SparkEnemy : public Enemy {
public: 
    SparkEnemy() = delete; //禁用默认构造
    SparkEnemy(sf::Sprite& sprite) : Enemy(sprite){
        setSpeed({0.015f,0});
        setHealth(10);
    };
    void update(float deltaTime, Background& bg) override;
    void takeDamage(int amount) override;

private:
    float elapsedTime = 0.0f;
};

#endif