#ifndef SPARK_ENEMY_H
#define SPARK_ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Enemy.h"
#include "const/Constants.h"

class SparkEnemy : public Enemy {
public: 
    SparkEnemy() = delete; //禁用默认构造
    SparkEnemy(std::shared_ptr<sf::Sprite> sprite) : Enemy(*sprite), m_spriteptr(sprite){
        setSpeed({0.015f,0});
        setHealth(5);
        m_attack = 1;
        m_type = 1;
    };
    void update(float deltaTime, Background& bg) override;

private:
    std::shared_ptr<sf::Sprite> m_spriteptr;
    float elapsedTime = 0.0f;
};

#endif