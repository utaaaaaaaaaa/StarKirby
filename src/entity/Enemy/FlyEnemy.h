#ifndef FLY_ENEMY_H
#define FLY_ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Enemy.h"
#include "const/Constants.h"

class FlyEnemy : public Enemy {
public: 
    FlyEnemy() = delete; //禁用默认构造
    FlyEnemy(std::shared_ptr<sf::Sprite> sprite) : Enemy(*sprite), m_spriteptr(sprite){
        setSpeed({0,0.015f});
        setHealth(3);
        m_attack = 2;
        m_type = 2;
    };
    void update(float deltaTime, Background& bg) override;

private:
    std::shared_ptr<sf::Sprite> m_spriteptr;
    float elapsedTime = 0.0f;
};

#endif