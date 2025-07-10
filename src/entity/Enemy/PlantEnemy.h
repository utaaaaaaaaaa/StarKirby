#ifndef PLANT_ENEMY_H
#define PLANT_ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Enemy.h"
#include "const/Constants.h"

class PlantEnemy : public Enemy {
public: 
    PlantEnemy() = delete; //禁用默认构造
    PlantEnemy(std::shared_ptr<sf::Sprite> sprite) : Enemy(*sprite), m_spriteptr(sprite){
        setSpeed({0,0});
        setHealth(3);
        m_attack = 1;
        m_type = 3;
    };
    void update(float deltaTime, Background& bg) override;

private:
    std::shared_ptr<sf::Sprite> m_spriteptr;
    float elapsedTime = 0.0f;
};

#endif